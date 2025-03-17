#include "customerdriver.h"
#include <iostream>
#include <string>
#include "customer.h"

const std::array<std::pair<int, std::string>, CustomerDriver::NUM_METHODS>
    CustomerDriver::METHODS = {{{1, "CreateCustomer"},
                                {2, "UpdateCustomer"},
                                {3, "ViewCustomer"},
                                {4, "ListAllCustomers"},
                                {5, "Exit"}}};

const std::array<std::pair<int, std::string>, CustomerDriver::NUM_FIELDS>
    CustomerDriver::FIELDS = {{{1, "Name"}, {2, "Email"}, {3, "Phone"}}};

void CustomerDriver::SelectCustomerAPI() {
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

                Customer::CreateCustomer(name, email, phone);
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

                Customer::UpdateCustomer(email, change_field, new_val);
                break;
            }
            case 3: {
            }
            case 4: {
            }
            case 5: {
                return;
            }
            default: {
                std::cout << "Unknown method: " << option << "\n";
                break;
            }
        }
        std::cout << "\n";
    }
}