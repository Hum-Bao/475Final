#include "shipping.h"

void Shipping::CreateShippingMethod(SAConnection& con, const std::string& type,
                                    const std::string& courier) {}

void Shipping::UpdateShippingMethod(SAConnection& con, const std::string& type,
                                    const std::string& courier,
                                    const std::string& update_field,
                                    const std::string& new_value) {}

void Shipping::ListAllShippingMethods(SAConnection& con) {}

void Shipping::ListPopularShippingMethods(SAConnection& con) {}

void Shipping::ListPopularShippingMethodsByRegion(SAConnection& con,
                                                  const std::string&& region) {}