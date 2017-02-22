#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include <vector>
#include "Headers/XRitBaseHeader.h"
#include "XRITHeader.h"
#include "Tools.h"

using namespace std;
namespace GOESDump {
    class FileParser {
        private:
            Tools Tools;

        public:
            XRITHeader GetHeader(vector<uint8_t> data);
    };
}

#endif