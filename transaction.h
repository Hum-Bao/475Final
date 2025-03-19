#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "SQLAPI/include/SQLAPI.h"

/*
Transaction API method declarations
Author(s): 
*/
class Transaction {
    public:
        static void CreateTransaction(
            SAConnection& con, const char& transaction_type,
            const std::string& customer_email, const std::string& facility_name,
            const std::string& shipping_method_type,
            const std::string& shipping_courier, const std::string& goods_SKU,
            const std::string& goods_quantity, const std::string& goods_weight);

        static void GetTransactionByCustomer(SAConnection& con,
                                             const std::string& customer_email);

        static void GetTransactionByFacility(SAConnection& con,
                                             const std::string& facility_name);

        //Maybe use std::time or ctime instead of string?
        static void GetTransactionByDateRange(SAConnection& con,
                                              const std::string& start_date,
                                              const std::string& end_date);
};
#endif