#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <thread>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>
#include "WatchMan.h"
#include <simple-web-server/server_http.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace GOESDump {
    typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

    class WebServer {
        private: 
            thread webserverThread;
            int port;
            HttpServer server;

        public:
            WebServer(int port) : webserverThread() {
                this->port = port;
            }

            ~WebServer(){
                if(webserverThread.joinable()) webserverThread.join();
            }

            void Start(WatchMan* wm){
                webserverThread = std::thread(&WebServer::Init, this, wm);
            }

            void Init(WatchMan* wm);
    }; 
}

#endif