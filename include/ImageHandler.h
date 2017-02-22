#ifndef _IMAGEHANDLER_H_
#define _IMAGEHANDLER_H_

#include <string>
#include "XRITHeader.h"

using namespace std;
namespace GOESDump {
    class ImageHandler {
        private: 

        public:
            ImageHandler() {}

            void HandleFile(string filename, string outputFolder);
            void ProcessCompressedFile(string file, XRITHeader header, string outputFolder);
            void ProcessFile(string file, XRITHeader header, string outputFolder);
    }; 
}

#endif