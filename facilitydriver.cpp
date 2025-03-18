#include "facilitydriver.h"
#include <iostream>
#include <string>
#include "facility.h"

const std::array<std::pair<int, std::string>, FacilityDriver::NUM_METHODS>
    GoodsDriver::METHODS = {{{1, "CreateFacility"},
                             {2, "UpdateFacility"},
                             {3, "SearchGoods"}}};

const std::array<std::pair<int, std::string>,FacilityDriver::NUM_FIELDS>
    FacilityDriver::FIELDS = {
        {{1, "NAME"}, {2, "REIGON"}}};

void FacilityDriver::SelectGoodsAPI(SAConnection& con) {
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

                std::cout << "\nEnter new value: ";
                std::getline(std::cin, new_val);

                Goods::UpdateGoods(con, SKU, change_field, new_val);
                break;
            }
            case 3: {
                Goods::ListAllGoods(con);
                break;
            }

        }
        std::cout << "\n";
    }
}
