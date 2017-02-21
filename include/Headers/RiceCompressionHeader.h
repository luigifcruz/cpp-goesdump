#ifndef _RICECOMPRESSIONHEADER_H
#define _RICECOMPRESSIONHEADER_H

#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    struct RiceCompressionRecord {
        uint8_t type;
        uint16_t size;

        uint16_t Flags;
        uint8_t Pixel;
        uint8_t Line;
    };

    class RiceCompressionHeader: public XRITBaseHeader {
        public:
            uint16_t Flags;
            uint8_t Pixel;
            uint8_t Line;
            
            RiceCompressionHeader(){}

            void Define(RiceCompressionRecord data) {
                Type = (HeaderType)131;
                Flags = data.Flags;
                Pixel = data.Pixel;
                Line = data.Line;
            }
    };
}

#endif