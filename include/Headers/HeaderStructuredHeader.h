#ifndef _HEADERSTRUCTUREDHEADER_H
#define _HEADERSTRUCTUREDHEADER_H

#include <string>
#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    struct HeaderStructuredRecord {
        uint8_t type;
        uint16_t size;
        
        string Data;
    };

    class HeaderStructuredHeader: public XRITBaseHeader {
        public:
            string Data;
            
            HeaderStructuredHeader(){}

            void Define(HeaderStructuredRecord data) {
                Type = (HeaderType)130;
                Data = data.Data;
            }
    };
}

#endif