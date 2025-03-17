#include "customerdriver.h"
#include <iostream>
#include "customer.h"

const std::array<std::pair<int, std::string>, 4> CustomerDriver::METHODS = {
    {{1, "CreateCustomer"},
     {2, "UpdateCustomer"},
     {3, "ViewCustomer"},
     {4, "ListAllCustomers"}}};

void CustomerDriver::SelectCustomerAPI() {
    std::cout << "Select API call: \n";
    for (const std::pair temp : METHODS) {
        std::cout << temp.first << ". " << temp.second << "\n";
    }
    int option = 0;
    std::cin >> option;
    switch (option) {
        case 1: {
            std::string name;
            std::string email;
            std::string phone;

            std::cout << "Enter customer name: ";
            std::cin >> name;

            std::cout << "\nEnter customer email: ";
            std::cin >> email;

            std::cout << "\nEnter customer phone number: ";
            std::cin >> phone;
            Customer::CreateCustomer(name, email, phone);
            break;
        }
        case 2: {
        }
        case 3: {
        }
        case 4: {
        }
        default: {
            std::cout << "Unknown method: " << option << "\n";
            break;
        }
    }
}