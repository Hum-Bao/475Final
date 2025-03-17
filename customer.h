#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "SQLAPI/include/SQLAPI.h"

/*
Customer API method declarations
Author(s): 
*/
class Customer {
    public:
        static void CreateCustomer(SAConnection& con, const std::string& name,
                                   const std::string& email,
                                   const std::string& phone);

        static void UpdateCustomer(SAConnection& con, std::string email,
                                   std::string change_field,
                                   std::string new_val);

        static void ViewCustomer(SAConnection& con, std::string email);

        static void ListAllCustomers(SAConnection& con);
};
#endif