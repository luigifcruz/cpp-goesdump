#include <iostream>
#include "Demuxer.h"

#define BUFFER_SIZE 892

using namespace std;
namespace GOESDump {
    packet Demuxer::CreatePacket(vector<uint8_t> data) {
        packet pk;
        pk.lastAPID = -1;
        while (true) {
            GOESDump::MSDU msdu;

            if (data.size() < 6) {
                pk.data = data;
                return pk;
            }
            
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

        bool firstOrSinglePacket = msdu.Sequence == FIRST_SEGMENT || msdu.Sequence == SINGLE_DATA;

        cout << ">> " << firstOrSinglePacket << "\n";

        Packets++;

        if (!msdu.Valid()) {
            cout << "Wrong CRC!" << "\n";
            CRCFails++;
        }

        if (!msdu.Valid() || !msdu.Full()) {
            cout << "Got a invalid MSDU :(" << "\n";
            cout << "New Packet for APID " << msdu.APID << " - Valid CRC: " << msdu.Valid() << " - Full: " << msdu.Full() << " - Remaining Bytes: " <<  msdu.RemainingData.size() << " - Frame Lost: " << msdu.FrameLost << "\n";
            cout << "  Total Size: " << (msdu.PacketLength + 2) << " Current Size: " << msdu.Data.size() << "\n";
        }

        GOESDump::FileParser fileParser;
        if (msdu.Sequence == FIRST_SEGMENT || msdu.Sequence == SINGLE_DATA) {
            fileHeader = fileParser.GetHeader(msdu.Data);
            if (msdu.Sequence == FIRST_SEGMENT) {
                startnum = msdu.PacketNumber;
            }
        } else if (msdu.Sequence == LAST_SEGMENT) {
            endnum = msdu.PacketNumber;
            if (startnum == -1) {
                cout << "NOT BIG DEAL: Orphan Packet. Dropping\n";
                return;
            }
        } else if (msdu.Sequence != SINGLE_DATA && startnum == -1) {
            cout << "NOT BIG DEAL: Orphan Packet. Dropping\n";
            return;
        }

        const char *path = "./channels/";
        struct stat st = {0};
        if (stat(path, &st) == -1) {
            mkdir(path, 0700);
        }

        switch (fileHeader.Compression()) {
            case LRIT_RICE: 
                filename << "channels/" << channelId << "/" << msdu.APID << "_" << msdu.Version << "_" << msdu.PacketNumber << ".lrit";
            break;
            default: // For 0, 2, 5 runs the default
                filename << "channels/" << channelId << "/" << msdu.APID << "_" << msdu.Version << ".lrit";
            break;
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
        
        cout << channelId << "-" << counter << "-" << fhp << "\n";

        data = (data+8);
        packet p;
        
        if (fhp != 2047) {
            if (lastAPID == -1 && buffer.size() > 0) {
                if (fhp > 0) {
                    buffer.insert(buffer.end(), data+fhp, data+BUFFER_SIZE-8);
                }         

                p = CreatePacket(buffer);
                if (p.lastAPID == -1) {
                    buffer = p.data;
                } else {
                    buffer.clear();
                }
            }

            if (lastAPID != -1) {
                if (fhp > 0) {
                    buffer.insert(buffer.end(), data+fhp, data+BUFFER_SIZE-8);
                    temporaryStorage[lastAPID].addDataBytes(buffer);
                }

                if (!temporaryStorage[lastAPID].Full()) {
                    //Maybe a bug?
                }

                temporaryStorage.erase(lastAPID);
                lastAPID = -1;
            }

            buffer.insert(buffer.end(), data+fhp, data+BUFFER_SIZE-8);
            p = CreatePacket(buffer);
            if (p.lastAPID == -1) {
                buffer = p.data;
            } else {
                buffer.clear();
            }
        } else {
            if (buffer.size() > 0) {
                buffer.insert(buffer.end(), data, data+BUFFER_SIZE-8);
                p = CreatePacket(buffer);
                if (p.lastAPID == -1) {
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
