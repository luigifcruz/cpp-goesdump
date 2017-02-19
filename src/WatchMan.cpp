#include <iostream>
#include <string>
#include <sstream>
#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    void WatchMan::Log(string message) {
        cout << message << "\n";
    }
}
