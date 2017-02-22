#ifndef _NOAASUBPRODUCT_H_
#define _NOAASUBPRODUCT_H_

#include <string>
#include "Types/ScannerSubProduct.h"

using namespace std;
namespace GOESDump {
    class NOAASubproduct {
        public:
            int ID;
            string Name;

            NOAASubproduct() {}

            NOAASubproduct(int id) {
                ID = id;
                Name = "Unknown";
            }

            NOAASubproduct(ScannerSubProduct::ScannerSubProduct id, string name) {
                ID = (ScannerSubProduct::ScannerSubProduct)id;
                Name = name;
            }

            NOAASubproduct(int id, string name) {
                ID = id;
                Name = name;
            }
    }; 
}

#endif