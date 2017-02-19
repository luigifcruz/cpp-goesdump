#include <iostream>
#include "Demuxer.h"

using namespace std;
namespace GOESDump {
    void Demuxer::ParseBytes(uint8_t* data) {
        channelId = (data[1] & 0x3F);

        uint32_t counter = *((uint32_t *) (data+2));
        counter = ((counter>>24)&0xff) | ((counter<<8)&0xff0000) | ((counter>>8)&0xff00) | ((counter<<24)&0xff000000);
        counter &= 0xFFFFFF00;
        counter = counter >> 8;

        if (lastFrame != -1 && lastFrame + 1 != counter) {
            cout << "Lost " << (counter - lastFrame - 1) << " frames.\n";
            if (lastAPID != -1) {
                temporaryStorage[lastAPID].FrameLost = true;
            }
        }

        if (lastFrame != -1) {
            frameDrops += counter - lastFrame - 1;
        }

        uint16_t cb = *((uint16_t *) (data+6));
        cb = (cb>>8) | (cb<<8);
        uint16_t fhp = (cb & 0x7FF);
        
        cout << channelId << "-" << counter << "-" << fhp << "\n";

        data = (data+8);
        if (fhp != 2047) {
            if (lastAPID == -1 && buffer.size() > 0) {
                cout << "BUFFED" << "\n";
            }
            //if (lastAPID != -1) {}
        } else {

        }
    }
}
