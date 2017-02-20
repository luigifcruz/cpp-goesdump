#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "WatchMan.h"
#include "Types/SequenceType.h"
#include "MSDU.h"

#ifndef _DEMUXER_H_
#define _DEMUXER_H_

typedef struct {
    int8_t lastAPID;
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
            string filename;
            vector<uint8_t> buffer;
            map<int,GOESDump::MSDU> temporaryStorage;
            packet CreatePacket(vector<uint8_t> data);
            void FinishMSDU(GOESDump::MSDU msdu);
            int Packets = 0;
            int CRCFails = 0;

        public:
            Demuxer() { }

            void ParseBytes(uint8_t* data);
    }; 
}

#endif