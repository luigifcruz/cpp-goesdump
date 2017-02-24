#ifndef _DATAHANDLER_H_
#define _DATAHANDLER_H_

#include <map>
#include <thread>
#include <iostream>
#include <SatHelper/sathelper.h>
#include "Demuxer.h"

using namespace std;
namespace GOESDump {
    class DataHandler {
        private: 
            int port;
            map<int, Demuxer> demuxers;
            thread dataThread;
            void DemuxManager(uint8_t* packet);

        public:
        DataHandler(int port) : dataThread() {
            this->port = port;
        }

        ~DataHandler(){
            if(dataThread.joinable()) dataThread.join();
        }

        void Start(){
            dataThread = std::thread(&DataHandler::Init, this);
        }

        void Init();
    }; 
}

#endif