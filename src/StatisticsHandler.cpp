#include "StatisticsHandler.h"

#define BUFFER_SIZE 4165

using namespace std;
namespace GOESDump {
    void StatisticsHandler::Init(WatchMan* wm) {
        SatHelper::TcpClient tcpClient((string)"127.0.0.1", port);
        char buffer[BUFFER_SIZE];

        try {
            tcpClient.Connect();
        } catch (SatHelperException &e) {
            wm->Log("[StatisticsHandler] Cannot connect to port " + to_string(port) + ".", 3);
            exit(0);
        }

        while (1) {
            try {
                tcpClient.WaitForData(BUFFER_SIZE, 2);
                tcpClient.Receive((char *)buffer, BUFFER_SIZE);
                memcpy(&StatisticsData, buffer, BUFFER_SIZE);
                wm->UpdateStatistics(StatisticsData);
                usleep(500000);
            } catch(SatHelper::SocketException &e) {
                tcpClient.Close();
                wm->Log("[StatisticsHandler] Client disconnected.", 3);
                cerr << "   " << e.what() << "\n";
                break;
            }
        }  
    }
}
