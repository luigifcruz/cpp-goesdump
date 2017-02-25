#ifndef _STATISTICSHANDLER_H_
#define _STATISTICSHANDLER_H_

#include <thread>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <SatHelper/sathelper.h>
#include "StatisticsStruct.h"
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    class StatisticsHandler {
        private: 
            int port;
            thread statisticsThread;
            StatisticsStruct StatisticsData;

        public:
            StatisticsHandler(int port) : statisticsThread() {
                this->port = port;
            }

            ~StatisticsHandler(){
                if(statisticsThread.joinable()) statisticsThread.join();
            }

            void Start(WatchMan* wm){
                statisticsThread = std::thread(&StatisticsHandler::Init, this, wm);
            }

            void Init(WatchMan* wm);
    }; 
}

#endif