#ifndef _PRIMARYHEADER_H
#define _PRIMARYHEADER_H

#include <cstdint>
#include <cstring>
#include "XRITBaseHeader.h"
#include "../Types/FileTypeCode.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct PrimaryRecord {
        uint8_t type;
        uint16_t size;

        uint8_t FileTypeCode;
        uint32_t HeaderLength;
        uint64_t DataLength;
    };
    #pragma pack(pop)

    class PrimaryHeader: public XRITBaseHeader {
        public:
            FileTypeCode FileType;
            uint32_t HeaderLength;
            uint64_t DataLength;
            
            PrimaryHeader(){}

            void Define(PrimaryRecord data) {
                Type = (HeaderType)0;
                FileType = (FileTypeCode)data.FileTypeCode;
                HeaderLength = data.HeaderLength;
                DataLength = data.DataLength;
            }
    };
}

#endif