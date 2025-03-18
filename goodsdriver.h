#ifndef GOODSDRIVER_H
#define GOODSDRIVER_H

#include <array>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

class GoodsDriver {
    public:
        static void SelectGoodsAPI(SAConnection& con);

    private:
        const static int NUM_METHODS = 10;
        const static int NUM_FIELDS = 4;
        const static std::array<std::pair<int, std::string>, NUM_METHODS>
            METHODS;
        const static std::array<std::pair<int, std::string>, NUM_FIELDS> FIELDS;
};
#endif
