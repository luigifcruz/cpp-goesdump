#ifndef _NOAASPECIFICHEADER_H
#define _NOAASPECIFICHEADER_H

#include "XRITBaseHeader.h"
#include "../Types/CompressionType.h"

using namespace std;
namespace GOESDump {
    struct NOAASpecificRecord {
        uint8_t type;
        uint16_t size;

        string Signature;
        uint16_t ProductID;
        uint16_t ProductSubID;
        uint16_t Parameter;
        uint8_t Compression;
    };

    class NOAASpecificHeader: public XRITBaseHeader {
        public:
            string Signature;
            NOAAProduct Product; // MAKE CLASS
            NOAASubproduct SubProduct; // MAKE CLASS
            uint16_t Parameter;
            CompressionType Compression;

            NOAASpecificHeader(NOAASpecificRecord data) {
                Type = (HeaderType)129;
                Signature = data.Signature;
                Product = Presets.GetProductById(data.ProductID); // MAKE CLASS
                SubProduct = Product.getSubProduct(data.ProductSubID); // MAKE CLASS
                Parameter = data.Parameter;
                Compression = (CompressionType)data.Compression;
            }
    };
}

#endif