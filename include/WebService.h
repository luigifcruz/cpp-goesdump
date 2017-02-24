#ifndef _WEBSERVICE_H_
#define _WEBSERVICE_H_

#include <thread>
#include <iostream>
#include <stdio.h>
#include <simple-web-server/server_http.hpp>
#include "WatchMan.h"

using namespace std;
namespace GOESDump {

    typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

    class WebService {
        private: 
            thread webserviceThread;
            int port;
            HttpServer server;

        public:
            WebService(int port) : webserviceThread() {
                this->port = port;
            }

            ~WebService(){
                if(webserviceThread.joinable()) webserviceThread.join();
            }

            void Start(WatchMan watchMan){
                webserviceThread = std::thread(&WebService::Init, this, watchMan);
            }

            void Init(WatchMan watchMan);
    }; 
}

#endif