#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include <vector>
#include <Headers/XRitBaseHeader.h>
#include <XRITHeader.h>

using namespace std;
namespace GOESDump {
    class FileParser {
        public:
            XRITHeader GetHeader(vector<uint8_t> data);
            vector<XRITBaseHeader> GetHeaderData(vector<uint8_t> data);
    };
}

#endif