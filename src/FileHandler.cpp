#include "FileHandler.h"

using namespace std;
namespace GOESDump {
    void FileHandler::HandleFile(string filename, XRITHeader fileHeader) {
        switch(fileHeader.Compression()) {
            case CompressionType::JPEG: {
                PacketManager.DumpFile(filename, fileHeader, "jpg");
                break;
            }
            case CompressionType::GIF: {
                PacketManager.DumpFile(filename, fileHeader, "gif");
                break;
            }
            default:
                break;
        }

        switch(fileHeader.Product().ID) {
            case NOAAProductID::WEATHER_DATA:
            case NOAAProductID::OTHER_SATELLITES_1:
            case NOAAProductID::OTHER_SATELLITES_2: {
                if (PacketManager.HandleWeatherData(filename, fileHeader)) { DefaultHandler(filename, fileHeader); }
                break;
            }
            case NOAAProductID::NOAA_TEXT: {
                if (PacketManager.HandleTextData(filename, fileHeader)) { DefaultHandler(filename, fileHeader); }
                break;
            }
            default:
                DefaultHandler(filename, fileHeader);
                break;
        }
    }

    void FileHandler::DefaultHandler(string filename, XRITHeader fileHeader) {
        string dir = Tools.GetDirectoryName(filename);
        string ofilename = fileHeader.Filename() == "" ? Tools.GetFileName(filename) : fileHeader.Filename(); 
        string f = PacketManager.FixFileFolder(dir, ofilename, fileHeader.Product(), fileHeader.SubProduct());

        if (Tools.FileExists(f)) {
            string timestamp = Tools.GetTimeNow();
            string ext = Tools.GetExtension(f);
            string append = "--dup-" + timestamp + ext;
            f.replace(f.find(ext), ext.length(), append);
        }

        cout << "Filename: " << f << endl;
        
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
