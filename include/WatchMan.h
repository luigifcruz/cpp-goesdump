#ifndef _WATCHMAN_H_
#define _WATCHMAN_H_

using namespace std;
namespace GOESDump {
    class WatchMan {
        private: 

        public:
            WatchMan() {
                cout << "[WatchMan] Invoked!" << endl;
            }

            void Log(string message);
    }; 
}

#endif