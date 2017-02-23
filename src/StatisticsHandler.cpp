#include "StatisticsHandler.h"
#define BUFFER_SIZE 4165

#pragma pack(push, 1)
struct Statistics_st {
    uint8_t scid;
    uint8_t vcid;
    uint64_t packetNumber;
    uint16_t vitErrors;
    uint16_t frameBits;
    int32_t rsErrors[4];
    uint8_t signalQuality;
    uint8_t syncCorrelation;
    uint8_t phaseCorrection;
    uint64_t lostPackets;
    uint16_t averageVitCorrections;
    uint8_t averageRSCorrections;
    uint64_t droppedPackets;
    int64_t receivedPacketsPerChannel[256];
    int64_t lostPacketsPerChannel[256];
    uint64_t totalPackets;
    uint32_t startTime;
    uint8_t syncWord[4];
    uint8_t frameLock;
};
#pragma pack(pop)

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

        cout << "[StatisticsHandler] Client connected to port " << port << "\n";

        while (1) {
            try {
                tcpClient.WaitForData(BUFFER_SIZE, 2);
                tcpClient.Receive((char *)buffer, BUFFER_SIZE);
                Statistics_st tmp;
                memcpy(&tmp, buffer, BUFFER_SIZE);
                cout << (int)tmp.signalQuality << "\n";
                cout << tmp.packetNumber << "\n";
                cout << tmp.totalPackets << "\n";
                cout << tmp.vitErrors << "\n";

            } catch(SatHelper::SocketException &e) {
                tcpClient.Close();
                cerr << "[StatisticsHandler] Client disconnected:\n";
                cerr << "   " << e.what() << "\n";
                break;
            }
        }  
    }
}
