#ifndef _NOAASPECIFICHEADER_H
#define _NOAASPECIFICHEADER_H

#include <cstdint>
#include <cstring>
#include "XRITBaseHeader.h"
#include "../Types/CompressionType.h"
#include "../NOAAProduct.h"
#include "../NOAASubproduct.h"
#include "../Presets.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct NOAASpecificRecord {
        uint8_t type;
        uint16_t size;

        string Signature;
        uint16_t ProductID;
        uint16_t ProductSubID;
        uint16_t Parameter;
        uint8_t Compression;
    };
    #pragma pack(pop)

    class NOAASpecificHeader: public XRITBaseHeader {
        public:
            string Signature;
            NOAAProduct Product;
            NOAASubproduct SubProduct;
            uint16_t Parameter;
            CompressionType Compression;
            Presets presets;
            bool Init = false;
            
            NOAASpecificHeader(){}

            void Define(NOAASpecificRecord data) {
                Type = (HeaderType)129;
                Signature = data.Signature;
                Product = presets.GetProductById(data.ProductID); 
                SubProduct = Product.getSubProduct(data.ProductSubID);
                Parameter = data.Parameter;
                Compression = (CompressionType)data.Compression;
                Init = true;
            }
    };
}

#endif