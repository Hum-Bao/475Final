#ifndef FACILITY_H
#define FACILITY_H

#include <string>

/*
Facility API method declarations
Author(s): 
*/
class Facility {
    public:
        void CreateFacility(std::string name, std::string region);

        void UpdateFacility(std::string name, std::string update_field);

        void ListAllFacilities();
};
#endif