#include "transactiondriver.h"
#include <iostream>
#include <string>
#include "SQLAPI/include/SQLAPI.h"
#include "transaction.h"

const std::array<std::pair<int, std::string>, CustomerDriver::NUM_METHODS>
    CustomerDriver::METHODS = {{{1, "CreateTransaction"},
                                {2, "GetTransactionByCustomer"},
                                {3, "GetTransactionByFacility"},
                                {4, "GetTransactionByDateRange"},
                                {5, "Return"}}};

const std::array<std::pair<int, std::string>, CustomerDriver::NUM_FIELDS>
    CustomerDriver::FIELDS = {{{1, "TYPE"}, {2, "TIME"}, {3, "SHIPPING"}, {4, "FACILITY"}, {5, "CUSTOMER"} {6, "NUMBER"}}};
