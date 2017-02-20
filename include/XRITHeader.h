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

            XRITHeader(vector<XRITBaseHeader> headers) {
                for(XRITBaseHeader header: headers) {
                    SetHeader(header);
                }
            }

            string Filename() {
                if (DCSFilenameHeader.Init) {
                    return DCSFilenameHeader.Filename;
                } else if (AnnotationHeader.Init) {
                    return AnnotationHeader.Filename;
                } else {
                    return NULL;
                }
            }

            CompressionType Compression() {
                if (NOAASpecificHeader.Init) {
                    return NOAASpecificHeader.Compression;
                } else if (ImageStructureHeader.Init) {
                    return ImageStructureHeader.Compression;
                } else {
                    return NO_COMPRESSION;
                }
            }

            bool IsCompressed() {
                return Compression() != NO_COMPRESSION;
            }

            NOAAProduct Product() {
                if (NOAASpecificHeader.Init) {
                    return NOAASpecificHeader.Product;
                } else {
                    GOESDump::NOAAProduct noaaProduct(-1);
                    return noaaProduct;
                }
            }

            NOAASubproduct SubProduct() {
                if (NOAASpecificHeader.Init) {
                    return NOAASpecificHeader.SubProduct;
                } else {
                    GOESDump::NOAASubproduct noaaSubproduct(-1);
                    return noaaSubproduct;
                }
            }

            void SetHeader(XRITBaseHeader header);
    };
}

#endif