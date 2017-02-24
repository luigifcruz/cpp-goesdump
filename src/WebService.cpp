#include "WebService.h"

using namespace std;
namespace GOESDump {
    void WebService::Init(WatchMan watchMan) {
        server.config.port = port;

        server.resource["^/info$"]["GET"]=[this](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            stringstream content_stream;
            content_stream << "<h1>GOES Dump</h1>";

            //cout << this->watchMan.SignalQuality() << endl;
            
            //find length of content_stream (length received using content_stream.tellp())
            content_stream.seekp(0, ios::end);
            
            *response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << content_stream.tellp() << "\r\n\r\n" << content_stream.rdbuf();
        };

        server.start();
    }
}

