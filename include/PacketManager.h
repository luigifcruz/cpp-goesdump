#ifndef _PACKETMANAGER_H_
#define _PACKETMANAGER_H_

#include <regex>
#include <string>
#include <iostream>
#include "XRITHeader.h"
#include "NOAAProduct.h"
#include "NOAASubproduct.h"
#include "Tools.h"
#include <szlib.h>

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

        public:
            string FixFileFolder(string dir, string filename, NOAAProduct product, NOAASubproduct subProduct);
            bool HandleWeatherData(string filename, XRITHeader header);
            bool HandleTextData(string filename, XRITHeader header);
            void DumpFile(string filename, XRITHeader fileHeader, string newExt);
            string Decompressor(string filename, int pixels);
            string Decompressor(string prefix, int pixels, int startnum, int endnum);
            int DecompressRICE(char *input, char *output, size_t inputLength, size_t outputLength, int bitsPerPixel, int pixelsPerBlock, int pixelsPerScanline, int mask);
    }; 
}

#endif