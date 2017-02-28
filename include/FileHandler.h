#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

#include <map>
#include <string>
#include <xrit/lib.h>
#include "PacketManager.h"
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    class FileHandler {
        private:
            XRIT::Tools Tools;
            PacketManager PacketManager;
            void DefaultHandler(string filename, XRIT::Header fileHeader, WatchMan* wm);

        public:
            void HandleFile(string filename, XRIT::Header fileHeader, WatchMan* wm);
    };
}

#endif