#ifndef TRANSACTIONDRIVER_H
#define TRANSACTIONDRIVER_H

#include <array>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

class TransactionDriver {
public:
    static void SelectTransactionAPI(SAConnection& con);

private:
    const static int NUM_METHODS = 5; // Fixed to match array size
    const static int NUM_FIELDS = 6;  // Fixed to match array size

    const static std::array<std::pair<int, std::string>, NUM_METHODS> METHODS;
    const static std::array<std::pair<int, std::string>, NUM_FIELDS> FIELDS;
};

#endif
