#include <iostream>
#include <stdio.h>
#include "WebServer.h"

using namespace std;
namespace GOESDump {
    WebServer::WebServer(int port) {
        this->port = port;
    }

    int WebServer::ServeFile(char * filename) {
        this->filename = filename;

        FILE *sendFile = fopen(this->filename, "r");
        if (sendFile == NULL) 
            return 0;

        return 1;
    }
}

