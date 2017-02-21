#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
            // Make'em
            string GetDirectoryName(string d) {
                cout << "GetDirectoryName: " << d << endl;
                return "./channels";
            };

            string GetFileName(string d) {
                cout << "GetFileName: " << d << endl;
                return "./channels";
            };

            string Combine(string one, string two) {
                cout << "Combine: " << one << endl;
                cout << "Combine: " << two << endl;
                return "./channels";
            };

            string Binary2String(vector<uint8_t> binary);
    }; 
}

#endif