#ifndef _IMAGESTRUCTUREHEADER_H
#define _IMAGESTRUCTUREHEADER_H

#include <cstdint>
#include <cstring>
#include "XRITBaseHeader.h"
#include "../Types/CompressionType.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct ImageStructureRecord {
        uint8_t type;
        uint16_t size;

        uint8_t BitsPerPixel;
        uint16_t Columns;
        uint16_t Lines;
        uint8_t Compression;
    };
    #pragma pack(pop)

    class ImageStructureHeader: public XRITBaseHeader {
        public:
            uint8_t BitsPerPixel;
            uint16_t Columns;
            uint16_t Lines;
            HeaderType::CompressionType Compression;
            bool Init = false;
            
            ImageStructureHeader(){}
            
            void Define(ImageStructureRecord data) {
                Type = HeaderType::ImageStructureRecord;
                BitsPerPixel = data.BitsPerPixel;
                Columns = data.Columns;
                Lines = data.Lines;
                Compression = (HeaderType::CompressionType)data.Compression;
                Init = true;
            }
    };
}

#endif