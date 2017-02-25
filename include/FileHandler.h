#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

#include <map>
#include <string>
#include <XRITHeader.h>
#include "PacketManager.h"
#include "Tools.h"
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    class FileHandler {
        private:
            Tools Tools;
            PacketManager PacketManager;
            void DefaultHandler(string filename, XRITHeader fileHeader, WatchMan* wm);

        public:
            void HandleFile(string filename, XRITHeader fileHeader, WatchMan* wm);
    };
}

#endif