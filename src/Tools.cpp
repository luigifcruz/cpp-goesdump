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

    string Tools::DirParentName(const char* path) {
        return "Botolo!";
    }

    int Tools::FileExists(const char* path) {
        return 1;
    }

    string Tools::Binary2String(vector<uint8_t> binary) {
        std::string s;
        for(uint8_t byte: binary) { s += to_string(byte); }
        return s;
    }
}
