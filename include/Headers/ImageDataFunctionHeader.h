#ifndef _IMAGEDATAFUNCTIONHEADER_H
#define _IMAGEDATAFUNCTIONHEADER_H

#include <string>
#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    struct ImageDataFunctionRecord {
        uint8_t type;
        uint16_t size;
        
        string Data;
    };

    class ImageDataFunctionHeader: public XRITBaseHeader {
        public:
            string Data;

            ImageDataFunctionHeader(ImageDataFunctionRecord data) {
                Type = (HeaderType)3;
                Data = data.Data;
            }
    };
}

#endif