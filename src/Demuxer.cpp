#include "Demuxer.h"

#define BUFFER_SIZE 892

using namespace std;
namespace GOESDump {
    packet Demuxer::CreatePacket(vector<uint8_t> data, WatchMan* wm) {
        packet pk;
        pk.lastAPID = -1;

        while (true) {
            if (data.size() < 6) {
                pk.data = data;
                return pk;
            }

            MSDU msdu;
            msdu.parseMSDU(data);

            if (msdu.APID != 2047) {
                temporaryStorage[msdu.APID] = msdu;
                pk.lastAPID = msdu.APID;
            } else {
                pk.lastAPID = -1;
            }

            if (msdu.RemainingData.size() > 0 || msdu.Full()) {
                data = msdu.RemainingData;
                msdu.RemainingData.clear();
                FinishMSDU(msdu, wm);
                temporaryStorage.erase(msdu.APID);
                pk.lastAPID = -1;
            } else {
                break;
            }
        }
        return pk;
    } 

    void Demuxer::FinishMSDU(MSDU msdu, WatchMan* wm) {
        if (msdu.APID == 2047) {
            // Skip fill packet
            return;
        }
        
        wm->Packets++;

        bool firstOrSinglePacket = msdu.Sequence == SequenceType::FIRST_SEGMENT || msdu.Sequence == SequenceType::SINGLE_DATA;

        /*if (!msdu.Valid()) {
            wm->Log("Wrong CRC!", 3);
            wm->CRCFails++;
        }

        if (!msdu.Valid() || !msdu.Full()) {
            wm->Log("Got a invalid MSDU :(", 3);
        }*/

        ostringstream filename;
        FileParser fileParser;

        if (msdu.Sequence == SequenceType::FIRST_SEGMENT || msdu.Sequence == SequenceType::SINGLE_DATA) {
            fileHeader = fileParser.GetHeader(msdu.Data);
            if (msdu.Sequence == SequenceType::FIRST_SEGMENT) {
                startnum = msdu.PacketNumber;
            }
        } else if (msdu.Sequence == SequenceType::LAST_SEGMENT) {
            endnum = msdu.PacketNumber;
            if (startnum == -1) {
                //wm->Log("Orphan Packet. Dropping...");
                return;
            }
        } else if (msdu.Sequence != SequenceType::SINGLE_DATA && startnum == -1) {
            //wm->Log("Orphan Packet. Dropping...");
            return;
        }

        ostringstream path;
        path << "./channels/" << channelId;
        if (!Tools.DirExists(path.str())) {
            Tools.CreateDir(path.str());
        }
        
        switch (fileHeader.Compression()) {
            case CompressionType::LRIT_RICE: {
                filename << "./channels/" << channelId << "/" << msdu.APID << "_" << msdu.Version << "_" << msdu.PacketNumber << ".lrit";
                break;
            }
            default:
                filename << "./channels/" << channelId << "/" << msdu.APID << "_" << msdu.Version << ".lrit";
            break;
        }

        vector<uint8_t> tmp = msdu.Data;
        tmp.erase(tmp.begin(), tmp.begin()+(firstOrSinglePacket ? 10 : 0));
        tmp.erase(tmp.begin()+(firstOrSinglePacket ? msdu.PacketLength - 10 : msdu.PacketLength), tmp.end());

        ofstream f(filename.str(), firstOrSinglePacket || fileHeader.Compression() == CompressionType::LRIT_RICE ? ios::out : ios::app | ios::binary);
        copy(tmp.begin(), tmp.end(), ostreambuf_iterator<char>(f));
        f.close();

        if (msdu.Sequence == SequenceType::LAST_SEGMENT || msdu.Sequence == SequenceType::SINGLE_DATA) {
            if (fileHeader.Compression() == CompressionType::LRIT_RICE) {
                string decompressed;
                if (msdu.Sequence == SequenceType::SINGLE_DATA) {
                    decompressed = PacketManager.Decompressor(filename.str(), fileHeader.ImageStructureHeader.Columns, wm);
                } else {
                    ostringstream packets;
                    packets << "./channels/" << channelId << "/" << msdu.APID << "_" << msdu.Version << "_";
                    decompressed = PacketManager.Decompressor(packets.str(), fileHeader.ImageStructureHeader.Columns, startnum, endnum, wm);
                }

                FileHandler.HandleFile(decompressed, fileHeader, wm);
                startnum = -1;
                endnum = -1;
            } else {
                FileHandler.HandleFile(filename.str(), fileHeader, wm);
            }
        }
    }

    void Demuxer::ParseBytes(uint8_t* data, WatchMan* wm) {
        channelId = (data[1] & 0x3F);

        uint32_t counter = *((uint32_t *) (data+2));
        counter = ((counter>>24)&0xff) | ((counter<<8)&0xff0000) | ((counter>>8)&0xff00) | ((counter<<24)&0xff000000);
        counter &= 0xFFFFFF00;
        counter = counter >> 8;

        if (lastFrame != -1 && lastFrame + 1 != counter) {
            wm->Log("Lost " + to_string(counter - lastFrame - 1) + " frames.");
            if (lastAPID != -1) {
                temporaryStorage[lastAPID].FrameLost = true;
            }
        }

        if (lastFrame != -1) {
            frameDrops += counter - lastFrame - 1;
        }

        uint16_t cb = *((uint16_t *) (data+6));
        cb = (cb>>8) | (cb<<8);
        uint16_t fhp = (cb & 0x7FF);
        
        //cout << channelId << "-" << counter << "-" << fhp << "\n";

        data = (data+8);
        packet p;
        p.lastAPID = 0;
        
        if (fhp != 2047) {
            if (lastAPID == -1 && buffer.size() > 0) {
                if (fhp > 0) {
                    buffer.insert(buffer.end(), data, data+fhp);
                }         

                p = CreatePacket(buffer, wm);
                lastAPID = p.lastAPID;

                if (lastAPID == -1) {
                    buffer = p.data;
                } else {
                    buffer.clear();
                }
            }

            if (lastAPID != -1) {
                if (fhp > 0) {
                    buffer.insert(buffer.end(), data, data+fhp);
                    temporaryStorage[lastAPID].addDataBytes(buffer);
                    buffer.clear();
                }

                if (!temporaryStorage[lastAPID].Full()) {
                    //Maybe a bug?
                }

                FinishMSDU(temporaryStorage[lastAPID], wm);
                temporaryStorage.erase(lastAPID);
                lastAPID = -1;
            }

            buffer.insert(buffer.end(), data+fhp, data+BUFFER_SIZE-8);
            p = CreatePacket(buffer, wm);
            lastAPID = p.lastAPID;
 
            if (lastAPID == -1) {
                buffer = p.data;
            } else {
                buffer.clear();
            }
        } else {
            if (buffer.size() > 0 && lastAPID != -1) {
                buffer.insert(buffer.end(), data, data+BUFFER_SIZE-8);
                p = CreatePacket(buffer, wm);
                lastAPID = p.lastAPID;
                if (lastAPID == -1) {
                    buffer = p.data;
                } else {
                    buffer.clear();
                }
            } else if (lastAPID == -1) {
                buffer.insert(buffer.end(), data, data+BUFFER_SIZE-8);
                p = CreatePacket(buffer, wm);
                lastAPID = p.lastAPID;
                if (lastAPID == -1) {
                    buffer = p.data;
                } else {
                    buffer.clear();
                }
            } else {
                vector<uint8_t> vecData;
                vecData.insert(vecData.end(), data, data+BUFFER_SIZE-8);
                temporaryStorage[lastAPID].addDataBytes(vecData);
            }
        }
    }
}
