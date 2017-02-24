#include "PacketManager.h"

using namespace std;
namespace GOESDump {
    
    string PacketManager::FixFileFolder(string dir, string filename, NOAAProduct product, NOAASubproduct subProduct) {
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

        return Tools.Combine("./" + dir, filename);;
    }

    bool PacketManager::HandleWeatherData(string filename, XRITHeader header) {
        if (header.PrimaryHeader.FileType == FileTypeCode::IMAGE) {
            string basedir = Tools.DirParentName(filename);
            if (header.Product().ID == (int)NOAAProductID::OTHER_SATELLITES_1 || header.Product().ID == (int)NOAAProductID::OTHER_SATELLITES_2) {
                basedir = Tools.Combine(basedir, OtherSatellitesFolder);
            } else {
                basedir = Tools.Combine(basedir, WeatherDataFolder);
            }

            cout << "New Weather Data - " << header.SubProduct().Name << " - " << header.Filename() << endl;
            //ImageHandler.Handler.HandleFile(filename, basedir);

            if (!Tools.Delete(filename)) {
                cout << "Failed to parse Weather Data Image at " << filename << endl;
            }
        } else {
            return true;
        }
        return false;
    }

    bool PacketManager::HandleTextData(string filename, XRITHeader header) {
        if (header.PrimaryHeader.FileType == FileTypeCode::TEXT) {
            string basedir = Tools.DirParentName(filename);
            basedir = Tools.Combine(basedir, TextFolder);

            cout << "New NOAA Text (" << header.Filename() << ")" << endl;
            //TextHandler.Handler.HandleFile(filename, basedir);

            if (!Tools.Delete(filename)) {
                cout << "Failed to parse Weather Data Image at " << filename << endl;
            }
        } else {
            return true;
        }
        return false;
    }

    void PacketManager::DumpFile(string filename, XRITHeader fileHeader, string newExt) {
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
                cout << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << fileHeader.Filename() << ") saved as " << Tools.GetFileName(f) << endl;
            } else {
                cout << "New " << fileHeader.Product().Name << " (" << fileHeader.Filename() << ") saved as " << Tools.GetFileName(f) << endl;
            }
        } else {
            if (fileHeader.SubProduct().Name != "Unknown") {
                cout << "New " << fileHeader.Product().Name << " - " << fileHeader.SubProduct().Name << " (" << fileHeader.Filename() << ")" << endl;
            } else {
                cout << "New " << fileHeader.Product().Name << " (" << fileHeader.Filename() << ")" << endl;
            }
        }

        cout << "Renaming " << filename << " to " << f << endl;
        /*FileStream fs = File.OpenRead(filename);
        fs.Seek(fileHeader.PrimaryHeader.HeaderLength, SeekOrigin.Begin);
        FileStream os = File.OpenWrite(f);

        byte[] buffer = new Byte[1024];
        int bytesRead;

        while ((bytesRead = fs.Read(buffer, 0, 1024)) > 0) {
            os.Write(buffer, 0, bytesRead);
        }

        fs.Close();
        os.Close();*/

        Tools.Move(filename, f.replace(f.find("." + newExt), newExt.length()+1, ".lrit"));
    }

    string PacketManager::Decompressor(string filename, int pixels) {
        return "s";
    }

    string PacketManager::Decompressor(string prefix, int pixels, int startnum, int endnum) {
        return "s";
    }

    int PacketManager::DecompressRICE(char *input, char *output, size_t inputLength, size_t outputLength, int bitsPerPixel, int pixelsPerBlock, int pixelsPerScanline, int mask) {
        SZ_com_t params;

        mask = mask | SZ_RAW_OPTION_MASK; // By default NOAA dont as for RAW, but their images are RAW. No Compression header.

        params.options_mask = mask;
        params.bits_per_pixel = bitsPerPixel;
        params.pixels_per_block = pixelsPerBlock;
        params.pixels_per_scanline = pixelsPerScanline;

        size_t destLen = pixelsPerScanline;
        int status = SZ_BufftoBuffDecompress(output, &destLen, input, inputLength, &params);

        return status != SZ_OK ? status : destLen;
    }
}