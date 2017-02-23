#include "Tools.h"

using namespace std;
namespace GOESDump {
    int Tools::CreateDir(const char* path) {
        return mkdir(path, 0700);
    }

    int Tools::DirExists(const char* path) {
        struct stat st = {0};
        return (stat(path, &st) == -1) ? 0 : 1;
    }

    string Tools::GetDirectoryName(string path) {
        boost::filesystem::path p(path);
        p.remove_filename();
        return p.string();
    };

    string Tools::DirParentName(const char* path) {
        boost::filesystem::path p(path);
        return p.parent_path().string();
    }

    string Tools::GetFileName(string path) {
        boost::filesystem::path p(path);
        return p.filename().string();
    };

    string Tools::GetExtension(string str) {
        return boost::filesystem::extension(str);
    }

    string Tools::Combine(string one, string two) {
        return (one+"/"+two);
    };

    int Tools::FileExists(const char* path) {
        return boost::filesystem::exists(path);
    }

    string Tools::GetTimeNow() {
        char buff[50];
        stringstream ss;
        time_t now = time(0);
        strftime(buff, 20, "%Y%m%d%H%M%S", localtime(&now));
        ss << buff;
        return ss.str();
    }

    int Tools::Move(string filename, string f) {
        return 1;
    }

    int Tools::Delete(string filename) {
        return 1;
    }

    string Tools::Binary2String(vector<uint8_t> binary) {
        string s = "";
        for(u_int8_t byte: binary) {
            s += static_cast<char>(byte);
        }
        return s;
    }
}
