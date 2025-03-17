#include "shippingdriver.h"
#include <iostream>
#include "shipping.h"

const std::array<std::pair<int, std::string>, ShippingDriver::NUM_METHODS>
    ShippingDriver::METHODS = {{{1, "CreateShippingMethod"},
                                {2, "UpdateShippingMethod"},
                                {3, "ListAllShippingMethods"},
                                {4, "ListPopularShippingMethods"},
                                {5, "ListPopularShippingMethodsByRegion"},
                                {6, "Exit"}}};

const std::array<std::pair<int, std::string>, ShippingDriver::NUM_FIELDS>
    ShippingDriver::FIELDS = {{{1, "TYPE"}, {2, "NAME"}}};

void ShippingDriver::SelectShippingAPI(SAConnection& con) {
    while (true) {
        std::cout << "Select API call: \n";
        for (const std::pair<int, std::string>& temp : METHODS) {
            std::cout << temp.first << ". " << temp.second << "\n";
        }
        int option = 0;
        std::cin >> option;
        switch (option) {
            case 1: {
                std::string type;
                std::string courier;
                std::cin.ignore();

                std::cout << "Enter shipping type: ";
                std::getline(std::cin, type);

                std::cout << "\nEnter shipping courier: ";
                std::getline(std::cin, courier);

                Shipping::CreateShippingMethod(con, type, courier);
                break;
            }
            case 2: {
                std::string type;
                std::string courier;
                std::string change_field;
                std::string new_val;
                std::cin.ignore();

                std::cout << "Enter shipping type: ";
                std::getline(std::cin, type);

                std::cout << "\nEnter shipping courier: ";
                std::getline(std::cin, courier);

                std::cout << "Select field to update: \n";
                for (const std::pair<int, std::string>& temp : FIELDS) {
                    std::cout << temp.first << ". " << temp.second << "\n";
                }
                std::string option;
                std::getline(std::cin, option);
                change_field = FIELDS[stoi(option) - 1].second;

                std::cout << "\nEnter new value: ";
                std::getline(std::cin, new_val);

                Shipping::UpdateShippingMethod(con, type, courier, change_field,
                                               new_val);
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