#include "PacketManager.h"

using namespace std;
namespace GOESDump {
    
    string PacketManager::FixFileFolder(string dir, string filename, XRIT::NOAAProduct product, XRIT::NOAASubproduct subProduct) {
        string basedir = Tools.DirParentName(dir);

        string folderName = UnknownDataFolder;
        if (product.ID == (int)NOAAProductID::SCANNER_DATA_1 || product.ID == (int)NOAAProductID::SCANNER_DATA_2) {
            switch (subProduct.ID) {
                case (int)ScannerSubProduct::INFRARED_AREA_OF_INTEREST:
                case (int)ScannerSubProduct::VISIBLE_AREA_OF_INTEREST:
                case (int)ScannerSubProduct::WATERVAPOUR_AREA_OF_INTEREST: {
                    folderName = Tools.Combine(ImagesFolder, "Area of Interest");
                    break;
                }
                case (int)ScannerSubProduct::INFRARED_FULLDISK:
                case (int)ScannerSubProduct::VISIBLE_FULLDISK:
                case (int)ScannerSubProduct::WATERVAPOUR_FULLDISK: {
                    folderName = Tools.Combine(ImagesFolder, "Full Disk");
                    break;
                }
                case (int)ScannerSubProduct::INFRARED_NORTHERN:
                case (int)ScannerSubProduct::VISIBLE_NORTHERN:
                case (int)ScannerSubProduct::WATERVAPOUR_NORTHERN: {
                    folderName = Tools.Combine(ImagesFolder, "Northern Hemisphere");
                    break;
                }
                case (int)ScannerSubProduct::INFRARED_SOUTHERN:
                case (int)ScannerSubProduct::VISIBLE_SOUTHERN:
                case (int)ScannerSubProduct::WATERVAPOUR_SOUTHERN: {
                    folderName = Tools.Combine(ImagesFolder, "Southern Hemisphere");
                    break;
                }
                case (int)ScannerSubProduct::INFRARED_UNITEDSTATES:
                case (int)ScannerSubProduct::VISIBLE_UNITEDSTATES:
                case (int)ScannerSubProduct::WATERVAPOUR_UNITEDSTATES: {
                    folderName = Tools.Combine(ImagesFolder, "United States");
                    break;
                }
                default:
                    folderName = Tools.Combine(ImagesFolder, UnknownDataFolder);
                    break;
            }
        } else {
            switch (product.ID) {
                case (int)NOAAProductID::DCS: {
                    folderName = DCSFolder;
                    break;
                }
                case (int)NOAAProductID::EMWIN: {
                    folderName = EMWINFolder;
                    break;
                }
                case (int)NOAAProductID::NOAA_TEXT: {
                    folderName = TextFolder;
                    break;
                }
                case (int)NOAAProductID::OTHER_SATELLITES_1:
                case (int)NOAAProductID::OTHER_SATELLITES_2: {
                    folderName = OtherSatellitesFolder;
                    break;
                }
                case (int)NOAAProductID::WEATHER_DATA: {
                    folderName = WeatherDataFolder;
                    break;
                }
                default:
                    folderName = UnknownDataFolder;
                    break;
            }
        }
         
        dir = Tools.Combine(basedir, folderName);

        if (!Tools.DirExists(dir)) {
            Tools.CreateDir(dir);
        }

        return Tools.Combine("./" + dir, filename);
    }

    bool PacketManager::HandleWeatherData(string filename, XRIT::Header header, WatchMan* wm) {
        if (header.PrimaryHeader.FileType == FileTypeCode::IMAGE) {
            string basedir = Tools.DirParentName(Tools.DirParentName(filename));
            if (header.Product().ID == NOAAProductID::OTHER_SATELLITES_1 || header.Product().ID == NOAAProductID::OTHER_SATELLITES_2) {
                basedir = Tools.Combine(basedir, OtherSatellitesFolder);
            } else {
                basedir = Tools.Combine(basedir, WeatherDataFolder);
            }

            wm->Log("New Weather Data - " + header.SubProduct().Name + " - " + header.Filename(), 1);

            if (!Tools.DirExists(basedir)) {
                Tools.CreateDir(basedir);
            }

            ImageHandler.HandleFile(filename, basedir, header);

            if (!Tools.Delete(filename)) {
                wm->Log("Failed to parse Weather Data Image at " + filename, 3);
            }
        } else {
            return true;
        }
        return false;
    }

    bool PacketManager::HandleTextData(string filename, XRIT::Header header, WatchMan* wm) {
        if (header.PrimaryHeader.FileType == FileTypeCode::TEXT) {
            string basedir = Tools.DirParentName(Tools.DirParentName(filename));
            basedir = Tools.Combine(basedir, TextFolder);

            wm->Log("New NOAA Text (" + header.Filename() + ")", 1);

            if (!Tools.DirExists(basedir)) {
                Tools.CreateDir(basedir);
            }

            TextHandler.HandleFile(filename, basedir, header);
            
            if (!Tools.Delete(filename)) {
                wm->Log("Failed to parse Weather Data Image at " + filename, 3);
            }
        } else {
            return true;
        }
        return false;
    }

    void PacketManager::DumpFile(string filename, XRIT::Header fileHeader, string newExt, WatchMan* wm) {
        ostringstream clog;
        string dir = Tools.GetDirectoryName(filename);
        string f = FixFileFolder(dir, fileHeader.Filename(), fileHeader.Product(), fileHeader.SubProduct());
        f.replace(f.find(".lrit"), 6, "." + newExt);

        if (Tools.FileExists(f)) {
            string timestamp = Tools.GetTimeNow();
            string ext = Tools.GetExtension(f);
            string append = "--dup-" + timestamp + ext;
            f.replace(f.find(ext), ext.length(), append);
        }

         if (Tools.GetFileName(f) != fileHeader.Filename()) {
            if (fileHeader.SubProduct().Name != "Unknown") {
                clog << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << fileHeader.Filename() << ") saved as " << Tools.GetFileName(f);
            } else {
                clog << "New " << fileHeader.Product().Name << " (" << fileHeader.Filename() << ") saved as " << Tools.GetFileName(f);
            }
        } else {
            if (fileHeader.SubProduct().Name != "Unknown") {
                clog << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << fileHeader.Filename() << ")";
            } else {
                clog << "New " << fileHeader.Product().Name << " (" << fileHeader.Filename() << ")";
            }
        }

        wm->Log(clog.str(), 1);
        wm->Log("Renaming " + filename + " to " + f);

        ifstream fs;
        ofstream os;

        fs.open(filename);
        fs.seekg(fileHeader.PrimaryHeader.HeaderLength);
        os.open(f);

        char *buffer = new char[1024];

        while (fs.read(buffer, 1024)) {
            os.write(buffer, fs.gcount());
        }

        if (fs.eof()) {
            if (fs.gcount() > 0) {
                os.write(buffer, fs.gcount());
            }
        }

        delete[] buffer;
        fs.close();
        os.close();

        Tools.Move(filename, f.replace(f.find("." + newExt), newExt.length()+1, ".lrit"));
    }

    string PacketManager::Decompressor(string filename, int pixels, WatchMan* wm) {
        ostringstream outputFile;
        outputFile << filename << "_decomp.lrit"; 

        char *outputData = new char[pixels];

        for (int z = 0; z < pixels; z++) {
            outputData[z] = 0x00;
        }

        vector<uint8_t> input = Tools.ReadAllBytes(filename);

        if (!AEC.Decompress(reinterpret_cast<char*>(input.data()), outputData, input.size(), sizeof(char)*pixels,
                            8, 16, pixels, AEC.ALLOW_K13_OPTION_MASK | AEC.MSB_OPTION_MASK | AEC.NN_OPTION_MASK)) {
            wm->Log("AEC Decompress problem decompressing file " + filename, 3);
            wm->Log("AEC Params: 8 - 16 - " + to_string(pixels), 3);
        }

        ofstream f(outputFile.str(), ios::out | ios::binary);
        f.write(outputData, sizeof(char)*pixels);
        f.close();

        return outputFile.str();
    }

    string PacketManager::Decompressor(string prefix, int pixels, int startnum, int endnum, WatchMan* wm) {
        ostringstream outputFile;
        ostringstream inputFile;
        vector<uint8_t> buffer;

        outputFile << prefix << "_decomp" << startnum << ".lrit"; 
        inputFile << prefix << startnum << ".lrit";

        vector<uint8_t> input = Tools.ReadAllBytes(inputFile.str());
        buffer.insert(buffer.end(), input.begin(), input.end());

        char *outputData = new char[pixels];
        int outputDataSize = sizeof(char)*pixels;
    
        startnum++;
        int overflowCaseLast = -1;

        if (endnum < startnum) {
            overflowCaseLast = endnum;
            endnum = 16383;
        }

        for (int i = startnum; i <= endnum; i++) {
            ostringstream ifile;
            ifile << prefix << i << ".lrit";

            input = Tools.ReadAllBytes(ifile.str());

            for (int z = 0; z < pixels; z++) {
                outputData[z] = 0x00;
            }

            if (!AEC.Decompress(reinterpret_cast<char*>(input.data()), outputData, input.size(), sizeof(char)*pixels,
                                8, 16, pixels, AEC.ALLOW_K13_OPTION_MASK | AEC.MSB_OPTION_MASK | AEC.NN_OPTION_MASK)) {
                wm->Log("AEC Decompress problem decompressing file " + ifile.str(), 3);
                wm->Log("AEC Params: 8 - 16 - " + to_string(pixels), 3);
            }
            // Fast buffering with vector.
            buffer.insert(buffer.end(), outputData, outputData+outputDataSize);
        }

        if (overflowCaseLast != -1) {
            cout << "CASE LAST" << endl;
            exit(0);
        }

        ofstream f(outputFile.str(), ios::out | ios::binary);
        copy(buffer.begin(), buffer.end(), ostreambuf_iterator<char>(f));
        f.close();

        return outputFile.str();
    }
}