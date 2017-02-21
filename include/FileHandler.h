#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

#include <map>
#include <string>
#include <XRITHeader.h>
#include "PacketManager.h"
#include "Tools.h"

using namespace std;
namespace GOESDump {
    typedef struct {
        string Filename;
        XRITHeader FileHeader;

        void Define(string filename, XRITHeader fileHeader) {
            Filename = filename;
            FileHeader = fileHeader;
        }
    } FileHandlerFunction;

    class FileHandler {
        private:
            Tools Tools;
            PacketManager PacketManager;
            map<int, FileHandlerFunction> byCompressionTypeHandler;
            map<int, FileHandlerFunction> byProductIdHandler;

        public:
            FileHandler() { }

            void AttachByCompressionHandler(int compressionType, FileHandlerFunction handler) {
                byCompressionTypeHandler[compressionType] = handler;
            }
            
            void AttachByProductIdHandler(int productId, FileHandlerFunction handler) {
                byProductIdHandler[productId] = handler;
            }

            void HandleFile(string filename, XRITHeader fileHeader);

            void DefaultHandler(string filename, XRITHeader fileHeader);
    };
}

#endif