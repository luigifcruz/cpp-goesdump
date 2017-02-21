#ifndef _DEMUXER_H_
#define _DEMUXER_H_

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include "WatchMan.h"
#include "FileParser.h"
#include "XRITHeader.h"
#include "Types/SequenceType.h"
#include "MSDU.h"

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
            ostringstream filename;
            vector<uint8_t> buffer;
            map<int,GOESDump::MSDU> temporaryStorage;
            packet CreatePacket(vector<uint8_t> data);
            void FinishMSDU(GOESDump::MSDU msdu);
            XRITHeader fileHeader;
            int Packets = 0;
            int CRCFails = 0;

        public:
            Demuxer() { }

            void ParseBytes(uint8_t* data);
    }; 
}

#endif