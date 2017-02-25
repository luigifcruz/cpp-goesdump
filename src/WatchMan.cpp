#include "WatchMan.h"

using namespace std;
namespace GOESDump {
    void WatchMan::Log(string out) {
        cout << out << endl;
        LogFile(out);
        AppendConsole(out, 4);
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
        AppendConsole(out, color);
        LogFile(out);
    }

    void WatchMan::LogFile(string log) {
        char buff[50];
        stringstream ss;
        time_t now = time(0);
        strftime(buff, 20, "%Y%m%d", localtime(&now));
        ss << buff;
        ofstream logFile("./logs/" + ss.str() + ".txt", std::ios_base::app | std::ios_base::out);
        strftime(buff, 20, "@%H:%M:%S", localtime(&now));
        ss << buff;
        logFile << ss.str() << " " << log << "\n"; 
        logFile.close();
    }

    void WatchMan::AppendConsole(string out, int color) {
        console newLog;
        newLog.text = out;
        newLog.color = color;
        ConsoleData.push_back(newLog);
        if(ConsoleData.size() > 10) {
            ConsoleData.erase(ConsoleData.begin(), ConsoleData.begin()+1);
        }
    }
}
