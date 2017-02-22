#ifndef _XRITHEADER_H_
#define _XRITHEADER_H_

#include <vector>
#include "Headers/AncillaryHeader.h"
#include "Headers/AnnotationHeader.h"
#include "Headers/DCSFilenameHeader.h"
#include "Headers/HeaderStructuredHeader.h"
#include "Headers/ImageDataFunctionHeader.h"
#include "Headers/ImageNavigationHeader.h"
#include "Headers/ImageStructureHeader.h"
#include "Headers/NOAASpecificHeader.h"
#include "Headers/PrimaryHeader.h"
#include "Headers/RiceCompressionHeader.h"
#include "Headers/SegmentIdentificationHeader.h"
#include "Headers/TimestampHeader.h"
#include "Headers/XRITBaseHeader.h"
#include "Types/CompressionType.h"
#include "NOAAProduct.h"
#include "NOAASubproduct.h"

using namespace std;
namespace GOESDump {
    class XRITHeader {
        public:
            AncillaryHeader AncillaryHeader;
            AnnotationHeader AnnotationHeader;
            DCSFilenameHeader DCSFilenameHeader;
            HeaderStructuredHeader HeaderStructuredHeader;
            ImageDataFunctionHeader ImageDataFunctionHeader;
            ImageNavigationHeader ImageNavigationHeader;
            ImageStructureHeader ImageStructureHeader;
            NOAASpecificHeader NOAASpecificHeader;
            PrimaryHeader PrimaryHeader;
            RiceCompressionHeader RiceCompressionHeader;
            SegmentIdentificationHeader SegmentIdentificationHeader;
            TimestampHeader TimestampHeader;
            vector<XRITBaseHeader> UnknownHeaders;

            XRITHeader() {
                
            }

            string Filename() {
                if (DCSFilenameHeader.Init) {
                    return DCSFilenameHeader.Filename;
                } else if (AnnotationHeader.Init) {
                    return AnnotationHeader.Filename;
                } else {
                    return "";
                }
            }

            HeaderType::CompressionType Compression() {
                if (NOAASpecificHeader.Init) {
                    return NOAASpecificHeader.Compression;
                } else if (ImageStructureHeader.Init) {
                    return ImageStructureHeader.Compression;
                } else {
                    return HeaderType::NO_COMPRESSION;
                }
            }

            bool IsCompressed() {
                return Compression() != HeaderType::NO_COMPRESSION;
            }

            NOAAProduct Product() {
                if (NOAASpecificHeader.Init) {
                    return NOAASpecificHeader.Product;
                } else {
                    return NOAAProduct(-1);
                }
            }

            NOAASubproduct SubProduct() {
                if (NOAASpecificHeader.Init) {
                    return NOAASpecificHeader.SubProduct;
                } else {
                    return NOAASubproduct(-1);
                }
            }
    };
}

#endif