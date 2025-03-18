#include "goodsdriver.h"
#include <iostream>

const std::array<std::pair<int, std::string>, GoodsDriver::NUM_METHODS>
    GoodsDriver::METHODS = {{{1, "CreateGoods"},
                             {2, "UpdateGoods"},
                             {3, "SearchGoods"},
                             {4, "ListAllGoods"},
                             {5, "GetGoodsVolumeByDate"},
                             {6, "GetTotalGoodsVolume"},
                             {7, "ListAllGoodsCategories"},
                             {8, "GetGoodsWeightByCategory"},
                             {9, "Return"}}};

const std::array<std::pair<int, std::string>, GoodsDriver::NUM_FIELDS>
    GoodsDriver::FIELDS = {
        {{1, "NAME"}, {2, "DESCRIPTION"}, {3, "SKU"}, {4, "CATEGORY"}}};

void GoodsDriver::SelectGoodsAPI(SAConnection& con) {
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
                Shipping::ListAllShippingMethods(con);
                break;
            }
            case 4: {
                Shipping::ListPopularShippingMethods(con);
                break;
            }
            case 5: {
                std::string region;

                std::cout << "Enter region: ";
                std::cin.ignore();
                std::getline(std::cin, region);
                std::cout << "\n";

                Shipping::ListPopularShippingMethodsByRegion(con, region);
                break;
            }
            case 6: {
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