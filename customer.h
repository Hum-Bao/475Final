#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

/*
Customer API method declarations
Author(s): 
*/
class Customer {
    public:
        static void CreateCustomer(std::string name, std::string email,
                                   std::string phone);

        static void UpdateCustomer(std::string email, std::string change_field,
                                   std::string new_val);

        static void ViewCustomer(std::string email);

        static void ListAllCustomers();
};
#endif