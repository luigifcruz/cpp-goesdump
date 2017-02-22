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

    string Tools::Combine(string one, string two) {
        return (one+"/"+two);
    };

    int Tools::FileExists(const char* path) {
        return boost::filesystem::exists(path);
    }

    string Tools::Binary2String(vector<uint8_t> binary) {
        std::string s;
        for(uint8_t byte: binary) { s += to_string(byte); }
        return s;
    }

    char* Tools::Vector2Byte(vector<uint8_t> vec) {
        char* data = nullptr;
        for(uint8_t byte: vec) {
            data += byte;
        }
        return data;
    }
}
