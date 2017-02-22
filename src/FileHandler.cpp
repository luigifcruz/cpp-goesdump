#include "FileHandler.h"

#include <iostream>

using namespace std;
namespace GOESDump {
    void FileHandler::HandleFile(string filename, XRITHeader fileHeader) {
        if (byCompressionTypeHandler.count((int)fileHeader.Compression())) {
            byCompressionTypeHandler[(int)fileHeader.Compression()].Define(filename, fileHeader);
        } else if (byProductIdHandler.count(fileHeader.Product().ID)) {
            byProductIdHandler[fileHeader.Product().ID].Define(filename, fileHeader);
        } else {
            DefaultHandler(filename, fileHeader);
        }
    }

    void FileHandler::DefaultHandler(string filename, XRITHeader fileHeader) {
        string dir = Tools.GetDirectoryName(filename);
        string ofilename = fileHeader.Filename() == "" ? Tools.GetFileName(filename) : fileHeader.Filename(); 
        string f = PacketManager.FixFileFolder(dir, ofilename, fileHeader.Product(), fileHeader.SubProduct());

        cout << "Filename: " << f << endl;

        if (Tools.FileExists(f)) {
            string timestamp = Tools.GetTimeNow();
            string ext = Tools.GetExtension(f);
            string append = "--dup-" + timestamp + ext;
            f.replace(f.find(ext), ext.length(), append);
        }

        
        if (Tools.GetFileName(f) != ofilename) {
            if (fileHeader.SubProduct().Name != "Unknown") {
                cout << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << ofilename << ") saved as " << Tools.GetFileName(f) << endl;
            } else {
                cout << "New " << fileHeader.Product().Name << " (" << ofilename << ") saved as " << Tools.GetFileName(f) << endl;
            }
        } else {
            if (fileHeader.SubProduct().Name != "Unknown") {
                cout << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << ofilename << ")" << endl;
            } else {
                cout << "New " << fileHeader.Product().Name << " (" << ofilename << ")" << endl;
            }
        }

        Tools.Move(filename, f);
    }
}
