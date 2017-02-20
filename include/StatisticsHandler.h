#ifndef _STATISTICSHANDLER_H_
#define _STATISTICSHANDLER_H_

#include <thread>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <SatHelper/sathelper.h>
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    class StatisticsHandler {
        private: 
            int port;
            thread statisticsThread;

        public:
            StatisticsHandler(int port) : statisticsThread() {
                this->port = port;
            }

            ~StatisticsHandler(){
                if(statisticsThread.joinable()) statisticsThread.join();
            }

            void Start(GOESDump::WatchMan watchMan){
                statisticsThread = std::thread(&StatisticsHandler::Init, this, watchMan);
            }

            void Init(GOESDump::WatchMan watchMan);
    }; 
}

#endif