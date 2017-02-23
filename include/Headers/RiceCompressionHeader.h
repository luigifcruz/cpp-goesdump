#ifndef _RICECOMPRESSIONHEADER_H
#define _RICECOMPRESSIONHEADER_H

#include <cstdint>
#include <cstring>
#include "XRITBaseHeader.h"
#include "../Tools.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct RiceCompressionRecord {
        uint8_t type;
        uint16_t size;

        uint16_t Flags;
        uint8_t Pixel;
        uint8_t Line;
    };
    #pragma pack(pop)

    class RiceCompressionHeader: public XRITBaseHeader {
        public:
            uint16_t Flags;
            uint8_t Pixel;
            uint8_t Line;
            
            RiceCompressionHeader(){}

            void Define(RiceCompressionRecord data) {
                Type = HeaderType::RiceCompressionRecord;
                Flags = data.Flags;
                Pixel = data.Pixel;
                Line = data.Line;
            }
    };
}

#endif