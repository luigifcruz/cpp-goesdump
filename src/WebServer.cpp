#include "WebServer.h"

using namespace std;
using boost::property_tree::ptree;
namespace GOESDump {
    void WebServer::Init(WatchMan* wm) {
        server.config.port = port;
        ifstream t("./lib/monitor.html");
        string str;

        str.assign((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        server.resource["^/$"]["GET"]=[&str](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            *response <<  "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-Length: " << str.size() << "\r\n\r\n" << str;
        };

        server.resource["^/data/files$"]["GET"]=[&wm](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            ptree out;
            ptree lst;

            for (boost::filesystem::recursive_directory_iterator end, dir("./channels"); dir != end; ++dir) {
                if (std::string::npos == dir->path().parent_path().string().find_first_of("0123456789")
                    && dir->path().filename().string() != ".DS_Store") {
                    ptree obj;
                    obj.put("path", dir->path().string());
                    obj.put("name", dir->path().filename().string());
                    //obj.put("date", boost::filesystem::last_write_time(dir).string());
                    lst.push_back(std::make_pair("", obj));
                }
            }

            out.add_child("Files", lst);

            ostringstream oss;
            boost::property_tree::write_json(oss, out);

            *response << "HTTP/1.1 200 OK\r\n"
                      << "Content-Type: application/json\r\n"
                      << "Content-Length: " << oss.str().length() << "\r\n\r\n"
                      << oss.str();
        };

        server.resource["^/data/console$"]["GET"]=[&wm](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            ptree out;
            ptree lst;

            for (int i=0; i<wm->ConsoleData.size(); i++) {
                ptree obj;
                obj.put("text",  wm->ConsoleData[i].text);
                obj.put("color", wm->ConsoleData[i].color);
                lst.push_back(std::make_pair("", obj));
            }

            out.add_child("Console", lst);

            ostringstream oss;
            boost::property_tree::write_json(oss, out);

            *response << "HTTP/1.1 200 OK\r\n"
                      << "Content-Type: application/json\r\n"
                      << "Content-Length: " << oss.str().length() << "\r\n\r\n"
                      << oss.str();
        };

        server.resource["^/data/fast$"]["GET"]=[&wm](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            ptree out;
            out.put("vitErrors",        (uint16_t)wm->StatisticsData.vitErrors);
            out.put("vcid",             (int)wm->StatisticsData.vcid);
            out.put("packetNumber",     (uint64_t)wm->StatisticsData.packetNumber);
            out.put("frameLock",        (int)wm->StatisticsData.frameLock);
            out.put("syncCorrelation",  (int)wm->StatisticsData.syncCorrelation);
            out.put("signalQuality",    (int)wm->StatisticsData.signalQuality);

            ostringstream oss;
            boost::property_tree::write_json(oss, out);
             
            *response << "HTTP/1.1 200 OK\r\n"
                      << "Content-Type: application/json\r\n"
                      << "Content-Length: " << oss.str().length() << "\r\n\r\n"
                      << oss.str();
        };

        server.resource["^/data/complete$"]["GET"]=[&wm](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            ptree out;
            out.put("scid",                     (int)wm->StatisticsData.scid);
            out.put("frameBits",                (uint16_t)wm->StatisticsData.frameBits);
            out.put("phaseCorrection",          (int)wm->StatisticsData.phaseCorrection);
            out.put("lostPackets",              (uint64_t)wm->StatisticsData.lostPackets);
            out.put("averageVitCorrections",    (uint16_t)wm->StatisticsData.averageVitCorrections);
            out.put("averageRSCorrections",     (int)wm->StatisticsData.averageRSCorrections);
            out.put("droppedPackets",           (uint64_t)wm->StatisticsData.droppedPackets);
            out.put("totalPackets",             (uint64_t)wm->StatisticsData.totalPackets);
            out.put("startTime",                (uint32_t)wm->StatisticsData.startTime);

            ostringstream oss;
            boost::property_tree::write_json(oss, out);
             
            *response << "HTTP/1.1 200 OK\r\n"
                      << "Content-Type: application/json\r\n"
                      << "Content-Length: " << oss.str().length() << "\r\n\r\n"
                      << oss.str();
        };

        server.default_resource["GET"]=[&str](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
            ifstream i("." + request->path);
            string image;
            image.assign((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
            i.close();
            
            *response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << image.size() << "\r\n\r\n" << image;
        };

        server.start();
        t.close();
    }
}
