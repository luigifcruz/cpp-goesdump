#ifndef _SEGMENTIDENTIFICATIONRECORD_H_
#define _SEGMENTIDENTIFICATIONRECORD_H_

#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    struct SegmentIdentificationRecord {
        uint8_t type;
        uint16_t size;

        uint16_t ImageID;
        uint16_t Sequence;
        uint16_t StartColumn;
        uint16_t StartLine;
        uint16_t MaxSegments;
        uint16_t MaxColumns;
        uint16_t MaxRows;
    };

    class SegmentIdentificationHeader: public XRITBaseHeader {
        public:
            uint16_t ImageID;
            uint16_t Sequence;
            uint16_t StartColumn;
            uint16_t StartLine;
            uint16_t MaxSegments;
            uint16_t MaxColumns;
            uint16_t MaxRows;

            SegmentIdentificationHeader(SegmentIdentificationRecord data) {
                Type = (HeaderType)128;
                ImageID = data.ImageID;
                Sequence = data.Sequence;
                StartColumn = data.StartColumn;
                StartLine = data.StartLine;
                MaxSegments = data.MaxSegments;
                MaxRows = data.MaxRows;
            }
    };
}

#endif