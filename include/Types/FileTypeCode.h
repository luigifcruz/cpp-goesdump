#ifndef _FILETYPECODE_H_
#define _FILETYPECODE_H_

enum FileTypeCode {
    UNKNOWN = -1,

    // By LRIT/HRIT Standard
    // Section 4 of LRIT/HRIT Global Specification, CGMS 03, August 12, 1999
    IMAGE = 0,
    MESSAGES = 1,
    TEXT = 2,
    ENCRYPTION_KEY = 3,
    RESERVED4 = 4,

    METEOROLOGICAL_DATA = 128,

    // NOAA
    DCS2 = 130,
    EMWIN2 = 214
};

#endif