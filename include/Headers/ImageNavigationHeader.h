#ifndef _IMAGENAVIGATIONHEADER_H
#define _IMAGENAVIGATIONHEADER_H

#include <string>
#include <cstdint>
#include <cstring>
#include "XRITBaseHeader.h"

using namespace std;
namespace GOESDump {
    #pragma pack(push, 1)
    struct ImageNavigationRecord {
        uint8_t type;
        uint16_t size;

        string ProjectionName;
        uint32_t ColumnScalingFactor;
        uint32_t LineScalingFactor;
        uint32_t ColumnOffset;
        uint32_t LineOffset;
    };
    #pragma pack(pop)

    class ImageNavigationHeader: public XRITBaseHeader {
        public:
            string ProjectionName;
            uint32_t ColumnScalingFactor;
            uint32_t LineScalingFactor;
            uint32_t ColumnOffset;
            uint32_t LineOffset;
            
            ImageNavigationHeader(){}

            void Define(ImageNavigationRecord data) {
                Type = HeaderType::ImageNavigationRecord;
                ProjectionName = data.ProjectionName;
                ColumnScalingFactor = data.ColumnScalingFactor;
                LineScalingFactor = data.LineScalingFactor;
                ColumnOffset = data.ColumnOffset;
                LineOffset = data.LineOffset;
            }
    };
}

#endif