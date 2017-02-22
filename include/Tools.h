#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/filesystem.hpp>

#include <iostream>

using namespace std;
namespace GOESDump {
    class Tools {
        private: 
            int DirExists(const char* path);
            int CreateDir(const char* path);
            string DirParentName(const char* path);
            int FileExists(const char* path);

        public:
            int CreateDir(string path) {
                return CreateDir(path.c_str());
            }
            
            int DirExists(string path) {
                return DirExists(path.c_str());
            }

            string DirParentName(string path) {
                return DirParentName(path.c_str());
            }

            int FileExists(string path) {
                return FileExists(path.c_str());
            }

            string GetDirectoryName(string path);

            string GetFileName(string d);

            string Combine(string one, string two);

            string Binary2String(vector<uint8_t> binary);

            char* Vector2Byte(vector<uint8_t> vec);
    }; 
}

#endif