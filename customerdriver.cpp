#include "customerdriver.h"
#include <iostream>
#include <string>
#include "SQLAPI/include/SQLAPI.h"
#include "customer.h"

void CustomerDriver::SelectCustomerAPI(SAConnection& con) {
    const std::array<std::pair<int, std::string>, CustomerDriver::NUM_METHODS>
        METHODS = {{{1, "CreateCustomer"},
                    {2, "UpdateCustomer"},
                    {3, "ViewCustomer"},
                    {4, "ListAllCustomers"},
                    {5, "Exit"}}};

    const std::array<std::pair<int, std::string>, CustomerDriver::NUM_FIELDS>
        FIELDS = {{{1, "NAME"}, {2, "EMAIL"}, {3, "PHONE"}}};
    while (true) {
        std::cout << "Select API call: \n";
        for (const std::pair<int, std::string>& temp : METHODS) {
            std::cout << temp.first << ". " << temp.second << "\n";
        }
        int option = 0;
        std::cin >> option;
        switch (option) {
            case 1: {
                std::string name;
                std::string email;
                std::string phone;
                std::cin.ignore();

                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);

                std::cout << "\nEnter customer email: ";
                std::getline(std::cin, email);

                std::cout << "\nEnter customer phone number: ";
                std::getline(std::cin, phone);

                std::cout << name << ", " << email << ", " << phone << "\n";

                Customer::CreateCustomer(con, name, email, phone);
                break;
            }
            case 2: {
                std::string email;
                std::string change_field;
                std::string new_val;
                std::cin.ignore();

                std::cout << "Enter customer email: ";
                std::getline(std::cin, email);

                std::cout << "Select field to update: \n";
                for (const std::pair<int, std::string>& temp : FIELDS) {
                    std::cout << temp.first << ". " << temp.second << "\n";
                }
                std::string option;
                std::getline(std::cin, option);
                change_field = FIELDS[stoi(option) - 1].second;

                std::cout << "\nEnter new value: ";
                std::getline(std::cin, new_val);

                std::cout << email << ", " << change_field << ", " << new_val
                          << '\n';

                Customer::UpdateCustomer(con, email, change_field, new_val);
                break;
            }
            case 3: {
                std::string email;
                std::cin.ignore();

                std::cout << "Enter customer email: ";
                std::getline(std::cin, email);

                std::cout << email << "\n";

                Customer::ViewCustomer(con, email);
                break;
            }
            case 4: {
                Customer::ListAllCustomers(con);
                break;
            }
            case 5: {
                return;
            }
            default: {
                std::cout << "Unknown method option: " << option << "\n";
                break;
            }
        }
        std::cout << "\n";
    }
}