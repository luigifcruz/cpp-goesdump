#ifndef _IMAGEHANDLER_H_
#define _IMAGEHANDLER_H_

#include <string>
#include <iostream>
#include "XRITHeader.h"
#include "Tools.h"
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    class ImageHandler {
        private: 
            Tools Tools;

        public:
            ImageHandler() {}

            void HandleFile(string filename, string outputFolder, XRITHeader header, WatchMan* wm);
            void ProcessCompressedFile(vector<uint8_t> file, XRITHeader header, string outputFolder, WatchMan* wm);
            void ProcessFile(vector<uint8_t> file, XRITHeader header, string outputFolder, WatchMan* wm);
    }; 
}

#endif