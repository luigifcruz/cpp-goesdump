#ifndef _PACKETMANAGER_H_
#define _PACKETMANAGER_H_

#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include "XRITHeader.h"
#include "NOAAProduct.h"
#include "NOAASubproduct.h"
#include "Tools.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "WatchMan.h"

extern "C" {
    #include <szlib.h>
}

using namespace std;
namespace GOESDump {
    class PacketManager {
        private: 
            string DCSFolder = "DCS";
            string ImagesFolder = "Images";
            string TextFolder = "Text";
            string EMWINFolder = "EMWIN";
            string WeatherDataFolder = "Weather Data";
            string OtherSatellitesFolder = "Other Satellites";
            string UnknownDataFolder = "Unknown";

            Tools Tools;
            ImageHandler ImageHandler;
            TextHandler TextHandler;

        public:
            string FixFileFolder(string dir, string filename, NOAAProduct product, NOAASubproduct subProduct);
            bool HandleWeatherData(string filename, XRITHeader header, WatchMan* wm);
            bool HandleTextData(string filename, XRITHeader header, WatchMan* wm);
            void DumpFile(string filename, XRITHeader fileHeader, string newExt, WatchMan* wm);
            string Decompressor(string filename, int pixels, WatchMan* wm);
            string Decompressor(string prefix, int pixels, int startnum, int endnum, WatchMan* wm);
            int DecompressRice(char *input, char *output, size_t inputLength, size_t outputLength, int bitsPerPixel, int pixelsPerBlock, int pixelsPerScanline, int mask);
    }; 
}

#endif