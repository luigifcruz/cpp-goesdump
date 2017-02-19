#include <map>
#include <thread>
#include <iostream>
#include <SatHelper/sathelper.h>
#include "WatchMan.h"
#include "Demuxer.h"

using namespace std;
namespace GOESDump {
    class DataHandler {
        private: 
            int port;
            map<int,GOESDump::Demuxer> demuxers;
            thread dataThread;
            void DemuxManager(uint8_t* packet);

        public:
        DataHandler(int port) : dataThread() {
            this->port = port;
        }

        ~DataHandler(){
            if(dataThread.joinable()) dataThread.join();
        }

        void Start(GOESDump::WatchMan watchMan){
            dataThread = std::thread(&DataHandler::Init, this, watchMan);
        }

        void Init(GOESDump::WatchMan watchMan);
    }; 
}