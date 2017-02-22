#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

#include <map>
#include <string>
#include <XRITHeader.h>
#include "PacketManager.h"
#include "Tools.h"

using namespace std;
namespace GOESDump {
    class FileHandler {
        private:
            Tools Tools;
            PacketManager PacketManager;
            void DefaultHandler(string filename, XRITHeader fileHeader);

        public:
            void HandleFile(string filename, XRITHeader fileHeader);
    };
}

#endif