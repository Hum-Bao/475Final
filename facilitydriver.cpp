#include "facilitydriver.h"
#include <iostream>
#include <string>
#include "facility.h"

const std::array<std::pair<int, std::string>, FacilityDriver::NUM_METHODS>
    FacilityDriver::METHODS = {{{1, "CreateFacility"},
                                {2, "UpdateFacility"},
                                {3, "ListAllFacilities"},
                                {4, "Return"}}};

const std::array<std::pair<int, std::string>, FacilityDriver::NUM_FIELDS>
    FacilityDriver::FIELDS = {{{1, "NAME"}, {2, "REGION"}}};

void FacilityDriver::SelectFacilityAPI(SAConnection& con) {
    while (true) {
        std::cout << "Select API call: \n";
        for (const std::pair<int, std::string>& method : METHODS) {
            std::cout << method.first << ". " << method.second << "\n";
        }

        int option = 0;
        std::cin >> option;
        std::cout << "\n";

        switch (option) {
            case 1: {
                std::string name;
                std::string region;
                std::cin.ignore();

                std::cout << "Enter facility name: ";
                std::getline(std::cin, name);

                std::cout << "Enter region: ";
                std::getline(std::cin, region);

                Facility::CreateFacility(con, name, region);
                break;
            }
            case 2: {
                std::string name;
                std::string update_field;
                std::string new_value;
                std::cin.ignore();

                std::cout << "Enter facility name: ";
                std::getline(std::cin, name);

                std::cout << "Select field to update: \n";
                for (const std::pair<int, std::string>& field : FIELDS) {
                    std::cout << field.first << ". " << field.second << "\n";
                }

                int field_option;
                std::cin >> field_option;

                update_field = FIELDS[field_option - 1].second;

                std::cout << "Enter new value for " << update_field << ": ";
                std::cin.ignore();
                std::getline(std::cin, new_value);

                Facility::UpdateFacility(con, name, update_field, new_value);
                break;
            }
            case 3: {
                Facility::ListAllFacilities(con);
                break;
            }
            case 4: {
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
