#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include "SQLAPI/include/SQLAPI.h"

/*
Facility API method declarations
Author(s): 
*/
class Facility {
    public:
        static void CreateFacility(SAConnection& con, const std::string& name,
                                   const std::string& region);

        static void UpdateFacility(SAConnection& con, const std::string& name,
                                   const std::string& update_field,
                                   const std::string& new_val);

        static void ListAllFacilities(SAConnection& con);

        static void ListAllRegions(SAConnection& con);
};
#endif