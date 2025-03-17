#ifndef SHIPPING_H
#define SHIPPING_H

#include <string>
#include "SQLAPI/include/SQLAPI.h"

/*
Shipping API method declarations
Author(s): 
*/
class Shipping {
    public:
        static void CreateShippingMethod(SAConnection& con,
                                         const std::string& type,
                                         const std::string& courier);

        static void UpdateShippingMethod(SAConnection& con,
                                         const std::string& type,
                                         const std::string& courier,
                                         const std::string& update_field,
                                         const std::string& new_value);

        static void ListAllShippingMethods(SAConnection& con);

        static void ListPopularShippingMethods(SAConnection& con);

        static void ListPopularShippingMethodsByRegion(
            SAConnection& con, const std::string&& region);
};
#endif