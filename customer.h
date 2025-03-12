#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
    public:
        std::string CreateCustomer(std::string name, std::string email,
                                   std::string phone);
        std::string UpdateCustomer(std::string email, std::string change_field,
                                   std::string new_val);
        std::string ViewCustomer(std::string email);
        std::string ListAllCustomers();
};
#endif