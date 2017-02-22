#ifndef _TIMESTAMPHEADER_H
#define _TIMESTAMPHEADER_H

#include <cstdint>
#include <cstring>
#include <ctime>
#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct TimestampRecord {
        uint8_t type;
        uint16_t size;

        uint16_t Days;
        uint32_t Milisseconds;

        time_t getDateTime() {
            /*DateTime t = new DateTime(1958, 1, 1);
            t.AddDays(Days);
            t.AddMilliseconds(Milisseconds);*/
            time_t time = 0;
            return time;
        }
    };
    #pragma pack(pop)

    class TimestampHeader: public XRITBaseHeader {
        public:
            time_t DateTime;
            
            TimestampHeader(){}

            void Define(TimestampRecord data) {
                Type = HeaderType::TimestampRecord;
                DateTime = data.getDateTime();
            }
    };
}

#endif