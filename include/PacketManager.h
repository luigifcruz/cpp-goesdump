#ifndef _PACKETMANAGER_H_
#define _PACKETMANAGER_H_

#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <xrit/lib.h>
#include "WatchMan.h"

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

            XRIT::Tools Tools;
            XRIT::ImageHandler ImageHandler;
            XRIT::TextHandler TextHandler;
            XRIT::AEC AEC;

        public:
            string FixFileFolder(string dir, string filename, XRIT::NOAAProduct product, XRIT::NOAASubproduct subProduct);
            bool HandleWeatherData(string filename, XRIT::Header header, WatchMan* wm);
            bool HandleTextData(string filename, XRIT::Header header, WatchMan* wm);
            void DumpFile(string filename, XRIT::Header fileHeader, string newExt, WatchMan* wm);
            string Decompressor(string filename, int pixels, WatchMan* wm);
            string Decompressor(string prefix, int pixels, int startnum, int endnum, WatchMan* wm);
    }; 
}

#endif