#include "shipping.h"
#include <iostream>

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
    SACommand select(&con, _TSA("SELECT * FROM SHIPPING"));
    select.Execute();

    SAString select_type;
    SAString select_courier;
    std::cout << "Showing " << select.RowsAffected() << " shipping methods\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        select_type = select[2].asString();
        select_courier = select[3].asString();
        std::cout << "Type: " << select_type.GetMultiByteChars() << "\n";
        std::cout << "Courier: " << select_courier.GetMultiByteChars() << "\n";
        std::cout << "\n";
    }
}

void Shipping::ListPopularShippingMethods(SAConnection& con) {}

void Shipping::ListPopularShippingMethodsByRegion(SAConnection& con,
                                                  const std::string& region) {}