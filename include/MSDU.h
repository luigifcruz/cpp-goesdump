#include <map>
#include <vector>
#include "SequenceType.h"

#ifndef _MSDU_H_
#define _MSDU_H_

using namespace std;
namespace GOESDump {
    class MSDU {
        private:
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

            MSDU() { }

            void addDataBytes(vector<uint8_t> data);

            GOESDump::MSDU parseMSDU(uint8_t data);

            bool Full() { 
                return Data.size() == PacketLength + 2;
            }

            uint16_t CRC() {
                /*uint16_t o = Data.Skip(Data.Length - 2).ToArray();
                if (BitConverter.IsLittleEndian) {
                    Array.Reverse(o);
                }
                return BitConverter.ToUInt16(o, 0);*/
            }

            bool Valid() {
                return true;
                //return Data.Take(Data.Length - 2).ToArray().CRC() == CRC;
            }

            bool FillPacket() {
                return APID == 2047;
            }

            void parseMSDU(vector<uint8_t> data);
    };
}

#endif