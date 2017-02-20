#ifndef _PRIMARYHEADER_H
#define _PRIMARYHEADER_H

#include "XRITBaseHeader.h"
#include "../Types/FileTypeCode.h"

using namespace std;
namespace GOESDump {
    struct PrimaryRecord {
        uint8_t type;
        uint16_t size;

        uint8_t FileTypeCode;
        uint32_t HeaderLength;
        uint64_t DataLength;
    };

    class PrimaryHeader: public XRITBaseHeader {
        public:
            FileTypeCode FileType;
            uint32_t HeaderLength;
            uint64_t DataLength;
            
            PrimaryHeader(){}

            PrimaryHeader(PrimaryRecord data) {
                Type = (HeaderType)0;
                FileType = (FileTypeCode)data.FileTypeCode;
                HeaderLength = data.HeaderLength;
                DataLength = data.DataLength;
            }
    };
}

#endif