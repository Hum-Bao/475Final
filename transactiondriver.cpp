#include "transactiondriver.h"
#include <iostream>
#include <string>
#include "SQLAPI/include/SQLAPI.h"
#include "transaction.h"

const std::array<std::pair<int, std::string>, TransactionDriver::NUM_METHODS>
    TransactionDriver::METHODS = {{{1, "CreateTransaction"},
                                   {2, "GetTransactionByCustomer"},
                                   {3, "GetTransactionByFacility"},
                                   {4, "GetTransactionByDateRange"},
                                   {5, "Return"}}};

const std::array<std::pair<int, std::string>, TransactionDriver::NUM_FIELDS>
    TransactionDriver::FIELDS = {{{1, "TYPE"},
                                  {2, "TIME"},
                                  {3, "SHIPPING"},
                                  {4, "FACILITY"},
                                  {5, "CUSTOMER"},
                                  {6, "NUMBER"}}};

void TransactionDriver::SelectTransactionAPI(SAConnection& con) {
    while (true) {
        std::cout << "Select API call: \n";
        for (const std::pair<int, std::string>& temp : METHODS) {
            std::cout << temp.first << ". " << temp.second << "\n";
        }
        int option = 0;
        std::cin >> option;
        std::cout << "\n";
        switch (option) {
            case 1: {
                char transaction_type;
                std::string customer_email;
                std::string facility_name;
                std::string shipping_method_type;
                std::string shipping_courier;
                std::string goods_SKU;
                std::string goods_quantity;
                std::string goods_weight;
                std::cin.ignore();

                std::cout << "Enter transaction type: ";
                std::cin >> transaction_type;
                std::cin.ignore();

                std::cout << "\nEnter customer email: ";
                std::getline(std::cin, customer_email);

                std::cout << "\nEnter facility name: ";
                std::getline(std::cin, facility_name);

                std::cout << "\nEnter shipping method type: ";
                std::getline(std::cin, shipping_method_type);

                std::cout << "\nEnter shipping courier: ";
                std::getline(std::cin, shipping_courier);

                std::cout << "\nEnter goods SKU: ";
                std::getline(std::cin, goods_SKU);

                std::cout << "\nEnter goods quantity: ";
                std::getline(std::cin, goods_quantity);

                std::cout << "\nEnter goods weight: ";
                std::getline(std::cin, goods_weight);
                std::cout << "\n";

                Transaction::CreateTransaction(
                    con, transaction_type, customer_email, facility_name,
                    shipping_method_type, shipping_courier, goods_SKU,
                    goods_quantity, goods_weight);
                break;
            }
            case 2: {
                std::string customer_email;
                std::cin.ignore();
                std::cout << "Enter customer email: ";
                std::getline(std::cin, customer_email);
                std::cout << "\n";

                Transaction::GetTransactionByCustomer(con, customer_email);

                break;
            }
            case 3: {
                std::string facility_name;
                std::cin.ignore();
                std::cout << "Enter facility name: ";
                std::getline(std::cin, facility_name);
                std::cout << "\n";

                Transaction::GetTransactionByFacility(con, facility_name);
                break;
            }
            case 4: {
                std::string start_date;
                std::string end_date;
                std::cin.ignore();

                std::cout << "Enter start date (YYYY-MM-DD): ";
                std::getline(std::cin, start_date);

                std::cout << "Enter end date (YYYY-MM-DD): ";
                std::getline(std::cin, end_date);
                std::cout << "\n";

                Transaction::GetTransactionByDateRange(con, start_date,
                                                       end_date);
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
