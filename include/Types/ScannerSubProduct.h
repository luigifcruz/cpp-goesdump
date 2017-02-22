#ifndef _SCANNERSUBPRODUCT_H_
#define _SCANNERSUBPRODUCT_H_

namespace ScannerSubProduct {
    enum ScannerSubProduct {
        NONE = 0,

        // Infrared Images
        INFRARED_FULLDISK = 1,
        INFRARED_NORTHERN = 2,
        INFRARED_SOUTHERN = 3,
        INFRARED_UNITEDSTATES = 4,
        INFRARED_AREA_OF_INTEREST = 5,

        // Visible Images
        VISIBLE_FULLDISK = 11,
        VISIBLE_NORTHERN = 12,
        VISIBLE_SOUTHERN = 13,
        VISIBLE_UNITEDSTATES = 14,
        VISIBLE_AREA_OF_INTEREST = 15,

        // Water Vapour
        WATERVAPOUR_FULLDISK = 21,
        WATERVAPOUR_NORTHERN = 22,
        WATERVAPOUR_SOUTHERN = 23,
        WATERVAPOUR_UNITEDSTATES = 24,
        WATERVAPOUR_AREA_OF_INTEREST = 25
    };
}


#endif