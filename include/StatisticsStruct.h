#ifndef _STATISTICSSTRUCT_H_
#define _STATISTICSSTRUCT_H_

namespace GOESDump {
    #pragma pack(push, 1)
    struct StatisticsStruct {
        uint8_t scid;
        uint8_t vcid;
        uint64_t packetNumber;
        uint16_t vitErrors;
        uint16_t frameBits;
        int32_t rsErrors[4];
        uint8_t signalQuality;
        uint8_t syncCorrelation;
        uint8_t phaseCorrection;
        uint64_t lostPackets;
        uint16_t averageVitCorrections;
        uint8_t averageRSCorrections;
        uint64_t droppedPackets;
        int64_t receivedPacketsPerChannel[256];
        int64_t lostPacketsPerChannel[256];
        uint64_t totalPackets;
        uint32_t startTime;
        uint8_t syncWord[4];
        uint8_t frameLock;
    };
    #pragma pack(pop)
}

#endif