#include <string.h>
#include <vector>
#include <map>
#include "WatchMan.h"
#include "MSDU.h"

#ifndef _DEMUXER_H_
#define _DEMUXER_H_

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
            string filename;
            vector<uint8_t> buffer;
            map<int,GOESDump::MSDU> temporaryStorage;

        public:
            Demuxer() { }

            void ParseBytes(uint8_t* data);
    }; 
}

#endif