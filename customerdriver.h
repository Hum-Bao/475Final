#ifndef CUSTOMERDRIVER_H
#define CUSTOMERDRIVER_H

#include <array>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

class CustomerDriver {
    public:
        static void SelectCustomerAPI(const SAConnection& con);

    private:
        const static int NUM_METHODS = 5;
        const static int NUM_FIELDS = 3;
        const static std::array<std::pair<int, std::string>, NUM_METHODS>
            METHODS;
        const static std::array<std::pair<int, std::string>, NUM_FIELDS> FIELDS;
};

#endif
