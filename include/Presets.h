#ifndef _PRESETS_H_
#define _PRESETS_H_

#include <map>
#include <string>
#include "NOAAProduct.h"
#include "Types/NOAAProductID.h"

using namespace std;
namespace GOESDump {
    class Presets {
        public:
        static map<int, NOAAProduct> noaaProducts;

        Presets() {
            map<int, NOAASubproduct> tmp;
            noaaProducts[(int)NOAA_TEXT] = NOAAProduct(NOAA_TEXT, "NOAA Text");

            tmp = {
                { 0, NOAASubproduct(0, "None") },
                { 1, NOAASubproduct(1, "Infrared Full Disk") },
                { 3, NOAASubproduct(3, "Visible Full Disk") }
            };
            
            noaaProducts[(int)OTHER_SATELLITES_1] = NOAAProduct(OTHER_SATELLITES_1, "Other Satellites", tmp);

            tmp = {
                { 0, NOAASubproduct(0, "None") },
                { 1, NOAASubproduct(1, "Infrared Full Disk") },
                { 3, NOAASubproduct(3, "Visible Full Disk") }
            };

            noaaProducts[(int)OTHER_SATELLITES_2] = NOAAProduct(OTHER_SATELLITES_2, "Other Satellites", tmp);

            noaaProducts[(int)WEATHER_DATA] = NOAAProduct(WEATHER_DATA, "Weather Data");

            noaaProducts[(int)DCS] = NOAAProduct(DCS, "DCS");

            tmp = { // So far, only received GOES 13 images. Coecidence?
                { (int) NONE,                         NOAASubproduct(NONE,                          "None") },
                { (int) INFRARED_FULLDISK,            NOAASubproduct(INFRARED_FULLDISK,             "Infrared Full Disk") },
                { (int) INFRARED_NORTHERN,            NOAASubproduct(INFRARED_NORTHERN,             "Infrared Northern Hemisphere") },
                { (int) INFRARED_SOUTHERN,            NOAASubproduct(INFRARED_SOUTHERN,             "Infrared Southern Hemisphere") },
                { (int) INFRARED_UNITEDSTATES,        NOAASubproduct(INFRARED_UNITEDSTATES,         "Infrared United States") },
                { (int) INFRARED_AREA_OF_INTEREST,    NOAASubproduct(INFRARED_AREA_OF_INTEREST,     "Infrared Area of Interest") },
                { (int) VISIBLE_FULLDISK,             NOAASubproduct(VISIBLE_FULLDISK,              "Visible Full Disk") },
                { (int) VISIBLE_NORTHERN,             NOAASubproduct(VISIBLE_NORTHERN,              "Visible Northern Hemisphere") },
                { (int) VISIBLE_SOUTHERN,             NOAASubproduct(VISIBLE_SOUTHERN,              "Visible Southern Hemisphere") },
                { (int) VISIBLE_UNITEDSTATES,         NOAASubproduct(VISIBLE_UNITEDSTATES,          "Visible United States") },
                { (int) VISIBLE_AREA_OF_INTEREST,     NOAASubproduct(VISIBLE_AREA_OF_INTEREST,      "Visible Area of Interest") },
                { (int) WATERVAPOUR_FULLDISK,         NOAASubproduct(WATERVAPOUR_FULLDISK,          "Water Vapour Full Disk") },
                { (int) WATERVAPOUR_NORTHERN,         NOAASubproduct(WATERVAPOUR_NORTHERN,          "Water Vapour Northern Hemisphere") },
                { (int) WATERVAPOUR_SOUTHERN,         NOAASubproduct(WATERVAPOUR_SOUTHERN,          "Water Vapour Southern Hemisphere") },
                { (int) WATERVAPOUR_UNITEDSTATES,     NOAASubproduct(WATERVAPOUR_UNITEDSTATES,      "Water Vapour United States") },
                { (int) WATERVAPOUR_AREA_OF_INTEREST, NOAASubproduct(WATERVAPOUR_AREA_OF_INTEREST,  "Water Vapour Area of Interest") }
            };

            noaaProducts[(int)SCANNER_DATA_1] = NOAAProduct(SCANNER_DATA_1, "Scanner Image", tmp);

            tmp = { // So far, only received GOES 15 images. Coecidence? 
                { (int) NONE,                         NOAASubproduct(NONE,                          "None") },
                { (int) INFRARED_FULLDISK,            NOAASubproduct(INFRARED_FULLDISK,             "Infrared Full Disk") },
                { (int) INFRARED_NORTHERN,            NOAASubproduct(INFRARED_NORTHERN,             "Infrared Northern Hemisphere") },
                { (int) INFRARED_SOUTHERN,            NOAASubproduct(INFRARED_SOUTHERN,             "Infrared Southern Hemisphere") },
                { (int) INFRARED_UNITEDSTATES,        NOAASubproduct(INFRARED_UNITEDSTATES,         "Infrared United States") },
                { (int) INFRARED_AREA_OF_INTEREST,    NOAASubproduct(INFRARED_AREA_OF_INTEREST,     "Infrared Area of Interest") },
                { (int) VISIBLE_FULLDISK,             NOAASubproduct(VISIBLE_FULLDISK,              "Visible Full Disk") },
                { (int) VISIBLE_NORTHERN,             NOAASubproduct(VISIBLE_NORTHERN,              "Visible Northern Hemisphere") },
                { (int) VISIBLE_SOUTHERN,             NOAASubproduct(VISIBLE_SOUTHERN,              "Visible Southern Hemisphere") },
                { (int) VISIBLE_UNITEDSTATES,         NOAASubproduct(VISIBLE_UNITEDSTATES,          "Visible United States") },
                { (int) VISIBLE_AREA_OF_INTEREST,     NOAASubproduct(VISIBLE_AREA_OF_INTEREST,      "Visible Area of Interest") },
                { (int) WATERVAPOUR_FULLDISK,         NOAASubproduct(WATERVAPOUR_FULLDISK,          "Water Vapour Full Disk") },
                { (int) WATERVAPOUR_NORTHERN,         NOAASubproduct(WATERVAPOUR_NORTHERN,          "Water Vapour Northern Hemisphere") },
                { (int) WATERVAPOUR_SOUTHERN,         NOAASubproduct(WATERVAPOUR_SOUTHERN,          "Water Vapour Southern Hemisphere") },
                { (int) WATERVAPOUR_UNITEDSTATES,     NOAASubproduct(WATERVAPOUR_UNITEDSTATES,      "Water Vapour United States") },
                { (int) WATERVAPOUR_AREA_OF_INTEREST, NOAASubproduct(WATERVAPOUR_AREA_OF_INTEREST,  "Water Vapour Area of Interest") }
            };

            noaaProducts[(int)SCANNER_DATA_2] = NOAAProduct(SCANNER_DATA_2, "Scanner Image", tmp);

            noaaProducts[(int)EMWIN] = NOAAProduct(EMWIN, "EMWIN");
        }

        NOAAProduct GetProductById(int productId) {
            if (noaaProducts.count(productId)) {
                return (NOAAProduct)noaaProducts.at(productId);
            } else {
                return NOAAProduct(productId);
            }
        }
    }; 
}

#endif