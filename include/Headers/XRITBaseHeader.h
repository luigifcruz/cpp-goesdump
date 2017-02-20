#ifndef _XRITBASEHEADER_H_
#define _XRITBASEHEADER_H_

#include <vector>
#include "../Types/HeaderType.h"

using namespace std;
namespace GOESDump {
    class XRITBaseHeader {
        public:
            HeaderType Type;
            vector<uint8_t> RawData;

            XRITBaseHeader() {
                Type = Unknown;
            }

            XRITBaseHeader(HeaderType type, vector<uint8_t> rawData) {
                Type = type;
                RawData = rawData;
            }
    };
}

#endif