#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

/*
Transaction API method declarations
Author(s): 
*/
class Transaction {
    public:
        void CreateTransaction(char transaction_type,
                               std::string customer_email,
                               std::string facility_name,
                               std::string shipping_method_type,
                               std::string shipping_courier,
                               std::string goods_name,
                               std::string goods_quantity);

        void GetTransactionByCustomer(std::string customer_email);

        void GetTransactionByFacility(std::string facility_name);

        //Maybe use std::time or ctime instead of string?
        void GetTransactionByDateRange(std::string start_date,
                                       std::string end_date);
};
#endif