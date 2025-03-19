#include "shipping.h"
#include <iostream>
#include <map>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

void Shipping::CreateShippingMethod(SAConnection& con, const std::string& type,
                                    const std::string& courier) {
    std::map<std::string, int> shipping_types = std::map<std::string, int>();
    std::map<std::string, int> shipping_couriers = std::map<std::string, int>();

    SACommand select_type(&con, _TSA("SELECT * FROM ShippingType"));
    select_type.Execute();
    while (select_type.FetchNext()) {
        shipping_types[select_type[2].asString().GetMultiByteChars()] =
            select_type[1].asInt32();
    }

    SACommand select_courier(&con, _TSA("SELECT * FROM ShippingCourier"));
    select_courier.Execute();
    while (select_courier.FetchNext()) {
        shipping_couriers[select_courier[2].asString().GetMultiByteChars()] =
            select_courier[1].asInt32();
    }
    try {
        SACommand insert(&con, _TSA("INSERT INTO ShippingMethod (typeID, "
                                    "courierID) VALUES (:1, :2)"));

        insert << _TSA(shipping_types[type])
               << _TSA(shipping_couriers[courier]);
        insert.Execute();
    } catch (SAException& e) {
        std::cerr << e.ErrMessage().GetMultiByteChars() << "\n";
        return;
    }
    std::cout << "Successfully created Shipping Method with type: " << type
              << " and courier: " << courier << "\n";
}

void Shipping::UpdateShippingMethod(SAConnection& con, const std::string& type,
                                    const std::string& courier,
                                    const std::string& change_field,
                                    const std::string& new_val) {

    std::map<std::string, int> shipping_types = std::map<std::string, int>();
    std::map<std::string, int> shipping_couriers = std::map<std::string, int>();

    SACommand select_type(&con, _TSA("SELECT * FROM ShippingType"));
    select_type.Execute();
    while (select_type.FetchNext()) {
        shipping_types[select_type[2].asString().GetMultiByteChars()] =
            select_type[1].asInt32();
    }

    SACommand select_courier(&con, _TSA("SELECT * FROM ShippingCourier"));
    select_courier.Execute();
    while (select_courier.FetchNext()) {
        shipping_couriers[select_courier[2].asString().GetMultiByteChars()] =
            select_courier[1].asInt32();
    }
    try {
        //Get Shipping id
        SACommand select(&con,
                         _TSA("SELECT ID FROM ShippingMethod WHERE typeID = "
                              ":1 AND courierID = :2"));
        select << _TSA(shipping_types[type])
               << _TSA(shipping_couriers[courier]);
        select.Execute();

        if (select.FetchNext()) {
            int id = select[1].asInt32();

            //Update record
            std::string command = "UPDATE ShippingMethod SET " + change_field +
                                  " = :1 WHERE ID = :2";
            SACommand update(&con, _TSA(command.c_str()));
            if (change_field == "TYPEID") {
                update << _TSA(shipping_types[new_val]) << _TSA(id);
            } else {
                update << _TSA(shipping_couriers[new_val]) << _TSA(id);
            }

            update.Execute();
        } else {
            std::cerr << "Shipping method: " << type << ", " << courier
                      << " not found.\n";
        }
    } catch (SAException& e) {
        std::cerr << e.ErrMessage().GetMultiByteChars() << "\n";
        return;
    }
    std::cout << "Successfully updated shipping method\n";
}

void Shipping::ListAllShippingMethods(SAConnection& con) {
    std::map<int, std::string> shipping_types = std::map<int, std::string>();
    std::map<int, std::string> shipping_couriers = std::map<int, std::string>();

    SACommand select_type(&con, _TSA("SELECT * FROM ShippingType"));
    select_type.Execute();
    while (select_type.FetchNext()) {
        shipping_types[select_type[1].asLong()] = select_type[2].asString();
    }

    SACommand select_courier(&con, _TSA("SELECT * FROM ShippingCourier"));
    select_courier.Execute();
    while (select_courier.FetchNext()) {
        shipping_couriers[select_courier[1].asLong()] =
            select_courier[2].asString();
    }

    SACommand select_method(&con, _TSA("SELECT * FROM ShippingMethod"));
    select_method.Execute();

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

void Shipping::ListPopularShippingMethods(SAConnection& con) {
    std::map<int, std::string> shipping_types = std::map<int, std::string>();
    std::map<int, std::string> shipping_couriers = std::map<int, std::string>();

    SACommand select_type(&con, _TSA("SELECT * FROM ShippingType"));
    select_type.Execute();
    while (select_type.FetchNext()) {
        shipping_types[select_type[1].asLong()] = select_type[2].asString();
    }

    SACommand select_courier(&con, _TSA("SELECT * FROM ShippingCourier"));
    select_courier.Execute();
    while (select_courier.FetchNext()) {
        shipping_couriers[select_courier[1].asLong()] =
            select_courier[2].asString();
    }

    std::string command =
        "SELECT ShippingMethod.typeID, ShippingMethod.courierID, "
        "COUNT(Transaction.shippingID) AS usage_count FROM Transaction JOIN "
        "ShippingMethod ON "
        "Transaction.shippingID = ShippingMethod.ID GROUP BY "
        "ShippingMethod.typeID, ShippingMethod.courierID ORDER BY usage_count "
        "DESC, ShippingMethod.typeID ASC";

    SACommand select_method(&con, _TSA(command.c_str()));
    select_method.Execute();

    int shipping_type = 0;
    int shipping_courier = 0;
    int usage_count = 0;
    std::cout << "Showing " << select_method.RowsAffected()
              << " shipping methods\n";
    while (select_method.FetchNext()) {
        shipping_type = select_method[1].asInt32();
        shipping_courier = select_method[2].asInt32();
        usage_count = select_method[3].asInt32();

        std::cout << "Type: " << shipping_types[shipping_type] << "\n";
        std::cout << "Courier: " << shipping_couriers[shipping_courier] << "\n";
        std::cout << "Times used: " << usage_count << "\n";
        std::cout << "\n";
    }
}

void Shipping::ListPopularShippingMethodsByRegion(SAConnection& con,
                                                  const std::string& region) {
    std::map<int, std::string> shipping_types = std::map<int, std::string>();
    std::map<int, std::string> shipping_couriers = std::map<int, std::string>();

    SACommand select_type(&con, _TSA("SELECT * FROM ShippingType"));
    select_type.Execute();
    while (select_type.FetchNext()) {
        shipping_types[select_type[1].asLong()] = select_type[2].asString();
    }

    SACommand select_courier(&con, _TSA("SELECT * FROM ShippingCourier"));
    select_courier.Execute();
    while (select_courier.FetchNext()) {
        shipping_couriers[select_courier[1].asLong()] =
            select_courier[2].asString();
    }

    std::string region_command =
        "SELECT id FROM Region WHERE name = '" + region + "'";

    SACommand select_region(&con, _TSA(region_command.c_str()));
    select_region.Execute();
    int region_id = 0;
    if (select_region.FetchNext()) {
        region_id = select_region[1].asInt32();
    } else {
        std::cerr << "Region: " << region << " does not exist\n";
    }

    /*
    SELECT ShippingMethod.typeID, ShippingMethod.courierID, COUNT(Transaction.shippingID) AS usage_count
    FROM Transaction 
    JOIN ShippingMethod ON Transaction.shippingID = ShippingMethod.ID
    JOIN Facility ON Transaction.facilityid= Facility.id
    JOIN Region ON Facility.regionid = Region.id
    WHERE Region.id = 1
    GROUP BY ShippingMethod.typeID, ShippingMethod.courierID
    ORDER BY usage_count DESC, ShippingMethod.typeID ASC
    */
    std::string command =
        "SELECT ShippingMethod.typeID, ShippingMethod.courierID, "
        "COUNT(Transaction.shippingID) AS usage_count ";
    command += "FROM Transaction ";
    command +=
        "JOIN ShippingMethod ON Transaction.shippingID = "
        "ShippingMethod.ID ";
    command += "JOIN Facility ON Transaction.facilityid = Facility.id ";
    command += "JOIN Region ON Facility.regionid = Region.id ";
    command += "WHERE Region.id = " + std::to_string(region_id) + " ";
    command += "GROUP BY ShippingMethod.typeID, ShippingMethod.courierID ";
    command += "ORDER BY usage_count DESC, ShippingMethod.typeID ASC";

    SACommand select_method(&con, _TSA(command.c_str()));
    select_method.Execute();

    int shipping_type = 0;
    int shipping_courier = 0;
    int usage_count = 0;
    std::cout << "Showing " << select_method.RowsAffected()
              << " shipping methods\n";
    while (select_method.FetchNext()) {
        shipping_type = select_method[1].asInt32();
        shipping_courier = select_method[2].asInt32();
        usage_count = select_method[3].asInt32();

        std::cout << "Type: " << shipping_types[shipping_type] << "\n";
        std::cout << "Courier: " << shipping_couriers[shipping_courier] << "\n";
        std::cout << "Times used: " << usage_count << "\n";
        std::cout << "\n";
    }
}