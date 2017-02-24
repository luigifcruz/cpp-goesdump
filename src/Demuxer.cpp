#include "Demuxer.h"

#define BUFFER_SIZE 892

using namespace std;
namespace GOESDump {
    packet Demuxer::CreatePacket(vector<uint8_t> data) {
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
                FinishMSDU(msdu);
                temporaryStorage.erase(msdu.APID);
                pk.lastAPID = -1;
            } else {
                break;
            }
        }
        return pk;
    } 

    void Demuxer::FinishMSDU(GOESDump::MSDU msdu) {
        if (msdu.APID == 2047) {
            // Skip fill packet
            return;
        }
        
        Packets++;

        bool firstOrSinglePacket = msdu.Sequence == SequenceType::FIRST_SEGMENT || msdu.Sequence == SequenceType::SINGLE_DATA;

        /*if (!msdu.Valid()) {
            cout << "Wrong CRC!" << "\n";
            CRCFails++;
        }

        if (!msdu.Valid() || !msdu.Full()) {
            cout << "Got a invalid MSDU :(" << "\n";
            cout << "New Packet for APID " << msdu.APID << " - Valid CRC: " << msdu.Valid() << " - Full: " << msdu.Full() << " - Remaining Bytes: " <<  msdu.RemainingData.size() << " - Frame Lost: " << msdu.FrameLost << "\n";
            cout << "  Total Size: " << (msdu.PacketLength + 2) << " Current Size: " << msdu.Data.size() << "\n";
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
                //cout << "Orphan Packet. Dropping\n";
                return;
            }
        } else if (msdu.Sequence != SequenceType::SINGLE_DATA && startnum == -1) {
            //cout << "Orphan Packet. Dropping\n";
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

        ofstream FILE(filename.str(), firstOrSinglePacket || fileHeader.Compression() == CompressionType::LRIT_RICE ? ios::out : ios::app | ios::binary);
        copy(tmp.begin(), tmp.end(), ostreambuf_iterator<char>(FILE));

        cout << "FILE RESUME" << endl;
        cout << "Filename: " << fileHeader.Filename() << endl;
        cout << "Compression: " << fileHeader.Compression() << endl;
        cout << "IsCompressed: " << fileHeader.IsCompressed()<< endl;
        cout << "Product: " << fileHeader.Product().ID<< endl;

        if (msdu.Sequence == SequenceType::LAST_SEGMENT || msdu.Sequence == SequenceType::SINGLE_DATA) {
            if (fileHeader.Compression() == CompressionType::LRIT_RICE) {
                /* IMPLEMENT DECOMPRESSOR
                string decompressed;
                if (msdu.Sequence == SINGLE_DATA) {
                    decompressed = PacketManager.Decompressor(filename, fileHeader.ImageStructureHeader.Columns);
                } else {
                    decompressed = PacketManager.Decompressor(String.Format("channels/{0}/{1}_{2}_", channelId, msdu.APID, msdu.Version), fileHeader.ImageStructureHeader.Columns, startnum, endnum);
                }

                FileHandler.HandleFile(decompressed, fileHeader);
                startnum = -1;
                endnum = -1;*/
            } else {
                FileHandler.HandleFile(filename.str(), fileHeader);
            }
        }
    }

    void Demuxer::ParseBytes(uint8_t* data) {
        channelId = (data[1] & 0x3F);

        uint32_t counter = *((uint32_t *) (data+2));
        counter = ((counter>>24)&0xff) | ((counter<<8)&0xff0000) | ((counter>>8)&0xff00) | ((counter<<24)&0xff000000);
        counter &= 0xFFFFFF00;
        counter = counter >> 8;

        if (lastFrame != -1 && lastFrame + 1 != counter) {
            cout << "Lost " << (counter - lastFrame - 1) << " frames.\n";
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

                p = CreatePacket(buffer);
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

                FinishMSDU(temporaryStorage[lastAPID]);
                temporaryStorage.erase(lastAPID);
                lastAPID = -1;
            }

            buffer.insert(buffer.end(), data+fhp, data+BUFFER_SIZE-8);
            p = CreatePacket(buffer);
            lastAPID = p.lastAPID;
 
            if (lastAPID == -1) {
                buffer = p.data;
            } else {
                buffer.clear();
            }
        } else {
            if (buffer.size() > 0 && lastAPID != -1) {
                buffer.insert(buffer.end(), data, data+BUFFER_SIZE-8);
                p = CreatePacket(buffer);
                lastAPID = p.lastAPID;
                if (lastAPID == -1) {
                    buffer = p.data;
                } else {
                    buffer.clear();
                }
            } else if (lastAPID == -1) {
                buffer.insert(buffer.end(), data, data+BUFFER_SIZE-8);
                p = CreatePacket(buffer);
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
