#ifndef _IMAGENAVIGATIONHEADER_H
#define _IMAGENAVIGATIONHEADER_H

#include <string>
#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    struct ImageNavigationRecord {
        uint8_t type;
        uint16_t size;

        string ProjectionName;
        uint32_t ColumnScalingFactor;
        uint32_t LineScalingFactor;
        uint32_t ColumnOffset;
        uint32_t LineOffset;
    };

    class ImageNavigationHeader: public XRITBaseHeader {
        public:
            string ProjectionName;
            uint32_t ColumnScalingFactor;
            uint32_t LineScalingFactor;
            uint32_t ColumnOffset;
            uint32_t LineOffset;
            
            ImageNavigationHeader(){}

            ImageNavigationHeader(ImageNavigationRecord data) {
                Type = (HeaderType)2;
                ProjectionName = data.ProjectionName;
                ColumnScalingFactor = data.ColumnScalingFactor;
                LineScalingFactor = data.LineScalingFactor;
                ColumnOffset = data.ColumnOffset;
                LineOffset = data.LineOffset;
            }
    };
}

#endif