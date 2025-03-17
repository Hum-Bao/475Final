#ifndef SHIPPINGDRIVER_H
#define SHIPPINGDRIVER_H

#include <array>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

class ShippingDriver {
    public:
        static void SelectShippingAPI(SAConnection& con);

    private:
        const static int NUM_METHODS = 6;
        const static int NUM_FIELDS = 2;
        const static std::array<std::pair<int, std::string>, NUM_METHODS>
            METHODS;
        const static std::array<std::pair<int, std::string>, NUM_FIELDS> FIELDS;
};
#endif
