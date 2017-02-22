#ifndef _ANCILLARYHEADER_H
#define _ANCILLARYHEADER_H

#include <string>
#include <cstdint>
#include <cstring>
#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct AncillaryText {
        uint8_t type;
        uint16_t size;
        
        string Data;
    };
    #pragma pack(pop)

    class AncillaryHeader: public XRITBaseHeader {
        public:
            string Filename;

            AncillaryHeader() {}

            void Define(AncillaryText data) {
                Type = (HeaderType)6;
                Filename = data.Data;
            }
    };
}

#endif