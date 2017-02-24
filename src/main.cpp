#include <iostream>
#include <thread>
#include <SatHelper/sathelper.h>
#include "DataHandler.h"
#include "StatisticsHandler.h"

#define WEBUI_PORT 8081
#define STATS_PORT 5002
#define DATA_PORT 5001

int main(void) {
    GOESDump::StatisticsHandler statisticsHandler(STATS_PORT);
    GOESDump::DataHandler dataHandler(DATA_PORT);

    dataHandler.Start();
    //statisticsHandler.Start();

    return 0;
}