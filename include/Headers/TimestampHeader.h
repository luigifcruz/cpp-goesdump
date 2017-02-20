#ifndef _TIMESTAMPHEADER_H
#define _TIMESTAMPHEADER_H

#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    struct TimestampRecord {
        uint8_t type;
        uint16_t size;
        uint16_t Days;
        uint32_t Milisseconds;

        // MAKE DATA RECORD
    };

    class TimestampHeader: public XRITBaseHeader {
        public:
            time_t DateTime;

            TimestampHeader(TimestampRecord data) {
                Type = (HeaderType)5;
                // MAKE DATA RECORD
            }
    };
}

#endif