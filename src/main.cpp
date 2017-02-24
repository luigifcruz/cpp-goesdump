#include <iostream>
#include <thread>
#include <SatHelper/sathelper.h>
#include "DataHandler.h"
#include "StatisticsHandler.h"
#include "WebService.h"

#define WEBUI_PORT 8081
#define STATS_PORT 5002
#define DATA_PORT 5001

int main(void) {
    GOESDump::WatchMan watchMan;
    GOESDump::StatisticsHandler statisticsHandler(STATS_PORT);
    GOESDump::DataHandler dataHandler(DATA_PORT);
    GOESDump::WebService webService(WEBUI_PORT);

    dataHandler.Start(watchMan);
    //statisticsHandler.Start(watchMan);
    //webService.Start(watchMan);

    return 0;
}