#include "DataHandler.h"
#define BUFFER_SIZE 892
#define FILL_VCID 63

using namespace std;
namespace GOESDump {
    void DataHandler::DemuxManager(uint8_t* data, WatchMan* wm) {
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
                wm->Log("[DataHandler] Creating new demuxer for #" + to_string(vcid), 2);
                demuxers[vcid] = Demuxer();
            }

            demuxers[vcid].ParseBytes(data, wm);
        }
    }

    void DataHandler::Init(WatchMan* wm) {
        SatHelper::TcpClient tcpClient((string)"127.0.0.1", port);
        uint8_t data[BUFFER_SIZE];

        try {
            tcpClient.Connect();
        } catch (SatHelperException &e) {
            wm->Log("[DataHandler] Cannot connect to port " + to_string(port) + ".", 3);
            exit(0);
        }

        while (1) {
            try {
                tcpClient.WaitForData(BUFFER_SIZE, 2);
                tcpClient.Receive((char *)data, BUFFER_SIZE);
                DemuxManager(data, wm);
            } catch(SatHelper::SocketException &e) {
                tcpClient.Close();
                wm->Log("[DataHandler] Client disconnected.", 3);
                cerr << "   " << e.what() << "\n";
                break;
            }
        }  
    }
}
