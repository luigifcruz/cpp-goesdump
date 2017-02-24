#ifndef _WATCHMAN_H_
#define _WATCHMAN_H_

#include <iostream>
#include <string>
#include <sstream>
#include "StatisticsStruct.h" 

using namespace std;
namespace GOESDump {
    class WatchMan {
        private: 
            StatisticsStruct StatisticsData;

        public:
            WatchMan() {
                cout << "[WatchMan] Invoked!" << endl;
            }

            int SignalQuality() {
                return (int)StatisticsData.signalQuality;
            }

            void UpdateStatistics(StatisticsStruct newData) {
                StatisticsData = newData;
            }
    }; 
}

#endif