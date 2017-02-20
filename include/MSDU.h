#ifndef _MSDU_H_
#define _MSDU_H_

#include <map>
#include <vector>
#include "Types/SequenceType.h"

using namespace std;
namespace GOESDump {
    class MSDU {
        private:
            uint16_t CRC() {
                uint16_t o = ((uint16_t)Data.at(Data.size()-2) << 8) | Data.at(Data.size()-1);
                return (o>>8) | (o<<8);
            }

        public:
            bool FrameLost = false;
            int Version;
            int SHF;
            int APID;
            int Type;
            bool SecondHeader;
            SequenceType Sequence;
            int PacketNumber;
            int PacketLength;
            vector<uint8_t> Data;
            vector<uint8_t> RemainingData;

            void addDataBytes(vector<uint8_t> data);
            void parseMSDU(vector<uint8_t> data);
            GOESDump::MSDU parseMSDU(uint8_t data);

            MSDU() { }

            bool Full() { 
                return Data.size() == PacketLength + 2;
            }

            bool Valid() {
                return false;
                //return Data.Take(Data.Length - 2).ToArray().CRC() == CRC;
            }

            bool FillPacket() {
                return APID == 2047;
            }            
    };
}

#endif