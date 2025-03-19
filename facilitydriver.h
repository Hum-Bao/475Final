#ifndef FACILITYDRIVER_H
#define FACILITYDRIVER_H

#include <array>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

class FacilityDriver {
    public:
        static void SelectFacilityAPI(SAConnection& con);

    private:
        const static int NUM_METHODS = 4;
        const static int NUM_FIELDS = 2;
        const static std::array<std::pair<int, std::string>, NUM_METHODS>
            METHODS;
        const static std::array<std::pair<int, std::string>, NUM_FIELDS> FIELDS;
};
#endif
