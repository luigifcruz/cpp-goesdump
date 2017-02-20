#ifndef _IMAGESTRUCTUREHEADER_H
#define _IMAGESTRUCTUREHEADER_H

#include "XRITBaseHeader.h"
#include "../Types/CompressionType.h"

using namespace std;
namespace GOESDump {
    struct ImageStructureRecord {
        uint8_t type;
        uint16_t size;

        uint8_t BitsPerPixel;
        uint16_t Columns;
        uint16_t Lines;
        uint8_t Compression;
    };

    class ImageStructureHeader: public XRITBaseHeader {
        public:
            uint8_t BitsPerPixel;
            uint16_t Columns;
            uint16_t Lines;
            CompressionType Compression;
            bool Init = false;
            
            ImageStructureHeader(){}
            
            ImageStructureHeader(ImageStructureRecord data) {
                Type = (HeaderType)1;
                BitsPerPixel = data.BitsPerPixel;
                Columns = data.Columns;
                Lines = data.Lines;
                Compression = (CompressionType)data.Compression;
                Init = true;
            }
    };
}

#endif