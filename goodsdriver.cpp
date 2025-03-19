#include "goodsdriver.h"
#include <iostream>
#include <string>
#include "goods.h"

const std::array<std::pair<int, std::string>, GoodsDriver::NUM_METHODS>
    GoodsDriver::METHODS = {{{1, "CreateGoods"},
                             {2, "UpdateGoods"},
                             {3, "SearchGoods"},
                             {4, "ListAllGoods"},
                             {5, "GetGoodsVolumeByDate"},
                             {6, "GetTotalGoodsVolume"},
                             {7, "CreateGoodsCategory"},
                             {8, "ListAllGoodsCategories"},
                             {9, "GetGoodsWeightByCategory"},
                             {10, "Return"}}};

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
                std::string name;
                std::string description;
                std::string SKU;
                std::string category;
                std::cin.ignore();

                std::cout << "Enter goods name: ";
                std::getline(std::cin, name);

                std::cout << "\nEnter goods description: ";
                std::getline(std::cin, description);

                std::cout << "\nEnter goods SKU: ";
                std::getline(std::cin, SKU);

                std::cout << "\nEnter goods category ";
                std::getline(std::cin, category);

                Goods::CreateGoods(con, name, description, SKU, category);
                break;
            }
            case 2: {
                std::string SKU;
                std::string change_field;
                std::string new_val;
                std::cin.ignore();

                std::cout << "Enter goods SKU: ";
                std::getline(std::cin, SKU);

                std::cout << "Select field to update: \n";
                for (const std::pair<int, std::string>& temp : FIELDS) {
                    std::cout << temp.first << ". " << temp.second << "\n";
                }
                std::string option;
                std::getline(std::cin, option);
                change_field = FIELDS[stoi(option) - 1].second;
                if (change_field == "CATEGORY") {
                    change_field += "ID";
                }

                std::cout << "\nEnter new value: ";
                std::getline(std::cin, new_val);

                Goods::UpdateGoods(con, SKU, change_field, new_val);
                break;
            }
            case 3: {
                std::string name;
                std::cin.ignore();

                std::cout << "Enter goods name: ";
                std::getline(std::cin, name);
                std::cout << "\n";
                Goods::SearchGoods(con, name);
                break;
            }
            case 4: {
                Goods::ListAllGoods(con);
                break;
            }
            case 5: {
                std::string start_date;
                std::string end_date;
                std::cin.ignore();

                std::cout << "Enter start date (YYYY-MM-DD): ";
                std::getline(std::cin, start_date);

                std::cout << "\nEnter end date (YYYY-MM-DD): ";
                std::getline(std::cin, end_date);
                std::cout << "\n";

                Goods::GetGoodsVolumeByDate(con, start_date, end_date);
                break;
            }
            case 6: {
                Goods::GetTotalGoodsVolume(con);
                break;
            }
            case 7: {
                std::string name;
                std::cin.ignore();

                std::cout << "Enter category name: ";
                std::getline(std::cin, name);
                std::cout << "\n";

                Goods::CreateGoodsCategory(con, name);
                break;
            }
            case 8: {
                Goods::ListAllGoodsCategories(con);
                break;
            }
            case 9: {
                std::string name;
                std::cin.ignore();

                std::cout << "Enter category name: ";
                std::getline(std::cin, name);
                std::cout << "\n";

                Goods::GetGoodsWeightByCategory(con, name);
                break;
            }
            case 10: {
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