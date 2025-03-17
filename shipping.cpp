#include "shipping.h"
#include <iostream>
#include <map>

void Shipping::CreateShippingMethod(SAConnection& con, const std::string& type,
                                    const std::string& courier) {
    SACommand insert(
        &con, _TSA("INSERT INTO SHIPPING (TYPE, COURIER) VALUES (:1, :2)"));

    insert << _TSA(type.c_str()) << _TSA(courier.c_str());
    insert.Execute();
}

void Shipping::UpdateShippingMethod(SAConnection& con, const std::string& type,
                                    const std::string& courier,
                                    const std::string& change_field,
                                    const std::string& new_val) {
    //Get Shipping id
    SACommand select(
        &con, _TSA("SELECT ID FROM SHIPPING WHERE TYPE = :1 AND COURIER = :2"));
    select << _TSA(type.c_str()) << _TSA(courier.c_str());
    select.Execute();

    if (select.FetchNext()) {
        int id = select.Field(1).asLong();

        //Update record
        std::string command =
            "UPDATE CUSTOMER SET " + change_field + "= :1 WHERE ID = :2";
        SACommand update(&con, _TSA(command.c_str()));
        update << _TSA(new_val.c_str()) << id;
        update.Execute();
    } else {
        std::cerr << "Shipping method: " << type << ", " << courier
                  << " not found.\n";
    }
}

void Shipping::ListAllShippingMethods(SAConnection& con) {
    std::map<int, std::string> shipping_types = std::map<int, std::string>();
    std::map<int, std::string> shipping_couriers = std::map<int, std::string>();

    std::cout << "Enter\n";

    SACommand select_type(&con, _TSA("SELECT * FROM ShippingType"));
    select_type.Execute();
    while (select_type.FetchNext()) {
        shipping_types[select_type[1].asLong()] = select_type[2].asString();
    }

    std::cout << "Finish types\n";

    SACommand select_courier(&con, _TSA("SELECT * FROM ShippingCourier"));
    select_courier.Execute();
    while (select_courier.FetchNext()) {
        shipping_couriers[select_courier[1].asLong()] =
            select_courier[2].asString();
    }

    std::cout << "Finish couriers\n";

    SACommand select_method(&con, _TSA("SELECT * FROM ShippingMethod"));
    select_method.Execute();
    std::cout << "finish methods\n";

    int shipping_type = 0;
    int shipping_courier = 0;
    std::cout << "Showing " << select_method.RowsAffected()
              << " shipping methods\n";
    while (select_method.FetchNext()) {
        //Select[1] is the id
        shipping_type = select_method[2].asInt32();
        shipping_courier = select_method[3].asInt32();

        std::cout << "Type: " << shipping_types[shipping_type] << "\n";
        std::cout << "Courier: " << shipping_couriers[shipping_courier] << "\n";
        std::cout << "\n";
    }
}

void Shipping::ListPopularShippingMethods(SAConnection& con) {}

void Shipping::ListPopularShippingMethodsByRegion(SAConnection& con,
                                                  const std::string& region) {}