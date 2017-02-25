#include "FileHandler.h"

using namespace std;
namespace GOESDump {
    void FileHandler::HandleFile(string filename, XRITHeader fileHeader, WatchMan* wm) {
        switch(fileHeader.Compression()) {
            case CompressionType::JPEG: {
                PacketManager.DumpFile(filename, fileHeader, "jpg", wm);
                break;
            }
            case CompressionType::GIF: {
                PacketManager.DumpFile(filename, fileHeader, "gif", wm);
                break;
            }
            default:
                break;
        }

        switch(fileHeader.Product().ID) {
            case NOAAProductID::WEATHER_DATA:
            case NOAAProductID::OTHER_SATELLITES_1:
            case NOAAProductID::OTHER_SATELLITES_2: {
                if (PacketManager.HandleWeatherData(filename, fileHeader, wm)) { DefaultHandler(filename, fileHeader, wm); }
                break;
            }
            case NOAAProductID::NOAA_TEXT: {
                if (PacketManager.HandleTextData(filename, fileHeader, wm)) { DefaultHandler(filename, fileHeader, wm); }
                break;
            }
            default:
                DefaultHandler(filename, fileHeader, wm);
                break;
        }
    }

    void FileHandler::DefaultHandler(string filename, XRITHeader fileHeader, WatchMan* wm) {
        ostringstream clog;
        string dir = Tools.GetDirectoryName(filename);
        string ofilename = fileHeader.Filename() == "" ? Tools.GetFileName(filename) : fileHeader.Filename(); 
        string f = PacketManager.FixFileFolder(dir, ofilename, fileHeader.Product(), fileHeader.SubProduct());

        if (Tools.FileExists(f)) {
            string timestamp = Tools.GetTimeNow();
            string ext = Tools.GetExtension(f);
            string append = "--dup-" + timestamp + ext;
            f.replace(f.find(ext), ext.length(), append);
        }
        
        if (Tools.GetFileName(f) != ofilename) {
            if (fileHeader.SubProduct().Name != "Unknown") {
                clog << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << ofilename << ") saved as " << Tools.GetFileName(f);
            } else {
                clog << "New " << fileHeader.Product().Name << " (" << ofilename << ") saved as " << Tools.GetFileName(f);
            }
        } else {
            if (fileHeader.SubProduct().Name != "Unknown") {
                clog << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << ofilename << ")";
            } else {
                clog << "New " << fileHeader.Product().Name << " (" << ofilename << ")";
            }
        }

        wm->Log(clog.str(), 1);
        Tools.Move(filename, f);
    }
}
