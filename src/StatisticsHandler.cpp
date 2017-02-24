#include "StatisticsHandler.h"

#define BUFFER_SIZE 4165

using namespace std;
namespace GOESDump {
    void StatisticsHandler::Init(GOESDump::WatchMan watchMan) {
        SatHelper::TcpClient tcpClient((string)"127.0.0.1", port);
        char buffer[BUFFER_SIZE];

        try {
            tcpClient.Connect();
        } catch (SatHelperException &e) {
            cerr << "[StatisticsHandler] Cannot connect to port " << port << ".\n";
            exit(0);
        }

        while (1) {
            try {
                tcpClient.WaitForData(BUFFER_SIZE, 2);
                tcpClient.Receive((char *)buffer, BUFFER_SIZE);

                StatisticsStruct tmp;
                memcpy(&tmp, buffer, BUFFER_SIZE);
                watchMan.UpdateStatistics(tmp);

            } catch(SatHelper::SocketException &e) {
                tcpClient.Close();
                cerr << "[StatisticsHandler] Client disconnected:\n";
                cerr << "   " << e.what() << "\n";
                break;
            }
        }  
    }
}
