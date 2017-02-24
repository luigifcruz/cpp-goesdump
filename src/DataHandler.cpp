#include "DataHandler.h"
#define BUFFER_SIZE 892
#define FILL_VCID 63

using namespace std;
namespace GOESDump {
    void DataHandler::DemuxManager(uint8_t* data) {
        int vcid = (data[1] & 0x3F);
        if (vcid != FILL_VCID) {
            if (vcid == 0 || vcid == 1) {
                // Skip DCS and EMWIN
                return;
            }

            if (vcid == 31) { 
                // Skip DCS for HRIT
                return;
            }
            
            if (!demuxers.count(vcid)) {
                cout << "[DataHandler] Creating new demuxer for #" << (vcid) << "...\n";
                demuxers[vcid] = Demuxer();
            }

            demuxers[vcid].ParseBytes(data);
        }
    }

    void DataHandler::Init(WatchMan watchMan) {
        SatHelper::TcpClient tcpClient((string)"127.0.0.1", port);
        uint8_t data[BUFFER_SIZE];

        try {
            tcpClient.Connect();
        } catch (SatHelperException &e) {
            cerr << "[DataHandler] Cannot connect to port " << port << ".\n";
            exit(0);
        }

        while (1) {
            try {
                tcpClient.WaitForData(BUFFER_SIZE, 2);
                tcpClient.Receive((char *)data, BUFFER_SIZE);
                DemuxManager(data);
            } catch(SatHelper::SocketException &e) {
                tcpClient.Close();
                cerr << "[DataHandler] Client disconnected:\n";
                cerr << "   " << e.what() << "\n";
                break;
            }
        }  
    }
}
