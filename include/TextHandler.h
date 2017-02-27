#ifndef _TEXTHANDLER_H_
#define _TEXTHANDLER_H_

#include <string>
#include <iostream>
#include "XRITHeader.h"
#include "Tools.h"
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    class TextHandler {
        private: 
            Tools Tools;

        public:
            TextHandler() {}

            void HandleFile(string filename, string outputFolder, XRITHeader header, WatchMan* wm);
            void ProcessFile(vector<uint8_t> file, string outputFolder, XRITHeader header, WatchMan* wm);
    }; 
}

#endif