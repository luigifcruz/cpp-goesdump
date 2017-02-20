#include "XRITHeader.h"

using namespace std;
namespace GOESDump {
    void XRITHeader::SetHeader(XRITBaseHeader header) {
        switch (header.Type) {
            case (int)AncillaryTextRecord:
                AncillaryHeader = (AncillaryHeader)header;
                break;
            case (int)AnnotationRecord:
                AnnotationHeader = (AnnotationHeader)header;
                break;
            case (int)DCSFileNameRecord:
                DCSFilenameHeader = (DCSFilenameHeader)header;
                break;
            case (int)HeaderStructuredRecord:
                HeaderStructuredHeader = (HeaderStructuredHeader)header;
                break;
            case (int)ImageDataFunctionRecord:
                ImageDataFunctionHeader = (ImageDataFunctionHeader)header;
                break;
            case (int)ImageNavigationRecord:
                ImageNavigationHeader = (ImageNavigationHeader)header;
                break;
            case (int)ImageStructureRecord:
                ImageStructureHeader = (ImageStructureHeader)header;
                break;
            case (int)NOAASpecificHeader:
                NOAASpecificHeader = (NOAASpecificHeader)header;
                break;
            case (int)PrimaryHeader:
                PrimaryHeader = (PrimaryHeader)header;
                break;
            case (int)RiceCompressionRecord:
                RiceCompressionHeader = (RiceCompressionHeader)header;
                break;
            case (int)SegmentIdentificationRecord:
                SegmentIdentificationHeader = (SegmentIdentificationHeader)header;
                break;
            case (int)TimestampRecord:
                TimestampHeader = (TimestampHeader)header;
                break;
            default:
                UnknownHeaders.push_back(header);
                break;
        }
    }
}
