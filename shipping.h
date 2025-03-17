#ifndef SHIPPING_H
#define SHIPPING_H

#include <string>

class Shipping {
        void CreateShippingMethod(std::string type, std::string courier);

        void UpdateShippingMethod(std::string type, std::string courier,
                                  std::string update_field);

        void ListAllShippingMethods();

        void ListPopularShippingMethods();

        void ListPopularShippingMethodsByRegion(std::string region);
};
#endif