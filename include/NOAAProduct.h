#ifndef _NOAAPRODUCT_H_
#define _NOAAPRODUCT_H_

#include <map>
#include <string>
#include "NOAASubproduct.h"
#include "Types/NOAAProductID.h"

using namespace std;
namespace GOESDump {
    class NOAAProduct {
        public:
            int ID;
            string Name;
            map<int, NOAASubproduct> SubProducts;

            NOAAProduct() {}

            NOAAProduct(int id) {
                
            }

            NOAAProduct(int id, string name) {

            }

            NOAAProduct(NOAAProductID::NOAAProductID id, string name) {

            }

            NOAAProduct(NOAAProductID::NOAAProductID id, string name, map<int, NOAASubproduct> subProducts) {

            }

            NOAAProduct(int id, string name, map<int, NOAASubproduct> subProducts) {

            }

            NOAASubproduct getSubProduct(int id) {
                return NOAASubproduct();
            }
    }; 
}

#endif