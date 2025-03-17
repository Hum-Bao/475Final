#include "customer.h"
#include <algorithm>
#include <iostream>
#include "SQLAPI/include/SQLAPI.h"

void Customer::CreateCustomer(SAConnection& con, const std::string& name,
                              const std::string& email,
                              const std::string& phone) {
    SACommand insert(
        &con,
        _TSA("INSERT INTO CUSTOMER (NAME, EMAIL, PHONE) VALUES (:1, :2, :3)"));

    insert << _TSA(name.c_str()) << _TSA(email.c_str()) << _TSA(phone.c_str());
    insert.Execute();
}

void Customer::UpdateCustomer(SAConnection& con, std::string email,
                              std::string change_field, std::string new_val) {}

void Customer::ViewCustomer(SAConnection& con, std::string email) {}

void Customer::ListAllCustomers(SAConnection& con) {}