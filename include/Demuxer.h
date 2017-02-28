#ifndef _DEMUXER_H_
#define _DEMUXER_H_

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <sstream>
#include <fstream>
#include "WatchMan.h"
#include "FileHandler.h"
#include "PacketManager.h"
#include <xrit/lib.h>

typedef struct {
    int lastAPID;
    vector<uint8_t> data;
} packet;

using namespace std;
namespace GOESDump {
    class Demuxer {
        private:
            int channelId;
            int lastFrame = -1;
            int frameDrops = 0;
            int lastAPID = -1;
            int startnum = -1;
            int endnum = -1;
            vector<uint8_t> buffer;
            map<int, XRIT::MSDU> temporaryStorage;
            XRIT::Header fileHeader;
            FileHandler FileHandler;
            XRIT::Tools Tools;
            PacketManager PacketManager;

            packet CreatePacket(vector<uint8_t> data, WatchMan* wm);
            void FinishMSDU(XRIT::MSDU msdu, WatchMan* wm);

        public:
            Demuxer() { }
            void ParseBytes(uint8_t* data, WatchMan* wm);
    }; 
}

#endif