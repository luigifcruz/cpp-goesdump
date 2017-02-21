#include <iostream>
#include <thread>
#include <SatHelper/sathelper.h>
#include "DataHandler.h"
#include "StatisticsHandler.h"

#include <string>
#include "Tools.h"

#define WEBUI_PORT 8080
#define STATS_PORT 5002
#define DATA_PORT 5001

int main(void) {
    GOESDump::WatchMan watchMan;
    GOESDump::StatisticsHandler statisticsHandler(STATS_PORT);
    GOESDump::DataHandler dataHandler(DATA_PORT);

    /*GOESDump::Tools Tools;

    vector<uint8_t> helloWorld = {
        (uint8_t)01001000,
        (uint8_t)01100101,
        (uint8_t)01101100,
        (uint8_t)01101100,
        (uint8_t)01101111,
        (uint8_t)00100000,
        (uint8_t)01010111,
        (uint8_t)01101111,
        (uint8_t)01110010,
        (uint8_t)01101100,
        (uint8_t)01100100
    };

    cout << Tools.Binary2String(helloWorld) << endl;*/

    dataHandler.Start(watchMan);
    //statisticsHandler.Start(watchMan);

    return 0;
}