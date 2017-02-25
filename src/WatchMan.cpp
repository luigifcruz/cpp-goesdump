#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    void WatchMan::Log(string out) {
        cout << out << endl;
    }

    void WatchMan::Log(string out, int color) {
        switch(color) {
            case 1: 
                cout << KGRN << out << RST << endl;
                break;
            case 2: 
                cout << KBLU << out << RST << endl;
                break;
            case 3: 
                cout << KRED << out << RST << endl;
                break;
            default:
                 cout << out << endl;
                break;
        }
    }
}
