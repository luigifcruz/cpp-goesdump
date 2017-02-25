#ifndef _WATCHMAN_H_
#define _WATCHMAN_H_

#include <iostream>
#include <string>
#include <sstream>
#include "StatisticsStruct.h" 

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

using namespace std;
namespace GOESDump {
    class WatchMan {
        private: 
            StatisticsStruct StatisticsData;

        public:
            WatchMan() {
                cout << KYEL << "[WatchMan] Invoked!" << RST << endl;
            }

            int SignalQuality() {
                return (int)StatisticsData.signalQuality;
            }

            void UpdateStatistics(StatisticsStruct newData) {
                StatisticsData = newData;
            }

            void Log(string out);
            void Log(string out, int color);

            int Packets = 0;
            //int CRCFails = 0;
    }; 
}

#endif