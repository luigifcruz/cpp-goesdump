#ifndef _WATCHMAN_H_
#define _WATCHMAN_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
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
    typedef struct {
        string text;
        int color;
    } console;

    class WatchMan {
        private: 
            void LogFile(string log);
            
        public:
            WatchMan() {
                cout << KYEL << "[WatchMan] Invoked!" << RST << endl;
            }

            void UpdateStatistics(StatisticsStruct newData) {
                StatisticsData = newData;
            }

            void Log(string out);
            void Log(string out, int color);

            void AppendConsole(string out, int color);

            vector<console> ConsoleData;
            StatisticsStruct StatisticsData;
            int Packets = 0;
            int CRCFails = 0;
    }; 
}

#endif