#include "transaction.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include "SQLAPI/include/SQLAPI.h"

static std::string CurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Transaction::CreateTransaction(SAConnection& con,
                                    const char& transaction_type,
                                    const std::string& customer_email,
                                    const std::string& facility_name,
                                    const std::string& shipping_method_type,
                                    const std::string& shipping_courier,
                                    const std::string& goods_name,
                                    const std::string& goods_quantity) {

    std::map<std::string, int> shipping_types = std::map<std::string, int>();
    std::map<std::string, int> shipping_couriers = std::map<std::string, int>();

    SACommand select_shipping_types(&con, _TSA("SELECT * FROM ShippingType"));
    select_shipping_types.Execute();
    while (select_shipping_types.FetchNext()) {
        shipping_types
            [select_shipping_types[2].asString().GetMultiByteChars()] =
                select_shipping_types[1].asInt32();
    }

    SACommand select_shipping_couriers(&con,
                                       _TSA("SELECT * FROM ShippingCourier"));
    select_shipping_couriers.Execute();
    while (select_shipping_couriers.FetchNext()) {
        shipping_couriers
            [select_shipping_couriers[2].asString().GetMultiByteChars()] =
                select_shipping_couriers[1].asInt32();
    }

    SACommand check_shipping_method(
        &con, _TSA("SELECT id FROM ShippingMethod WHERE typeID = :1 "
                   "AND courierID = :2"));
    check_shipping_method << _TSA(shipping_types[shipping_method_type])
                          << _TSA(shipping_couriers[shipping_courier]);

    check_shipping_method.Execute();

    int shipping_id = 0;
    if (check_shipping_method.FetchNext() &&
        check_shipping_method[1].asInt32() == 0) {
        std::cerr << "Shipping type: " << shipping_method_type
                  << " with courier: " << shipping_courier
                  << " does not exist.\n";
        return;
    } else {
        shipping_id = check_shipping_method[1].asInt32();
    }

    SACommand check_facility(&con, "SELECT id FROM Facility WHERE name = :1");
    check_facility << _TSA(facility_name.c_str());
    check_facility.Execute();

    int facility_id = 0;
    if (check_facility.FetchNext() && check_facility[1].asInt32() == 0) {
        std::cerr << "Facility: " << facility_name << " does not exist\n";
        return;
    } else {
        facility_id = check_facility[1].asInt32();
    }

    SACommand check_customer(&con, "SELECT id FROM Customer WHERE email = :1");
    check_customer << _TSA(customer_email.c_str());
    check_customer.Execute();

    int customer_id = 0;
    if (check_customer.FetchNext() && check_customer[1].asInt32() == 0) {
        std::cerr << "Customer with email: " << customer_email
                  << " does not exist\n";
        return;
    } else {
        customer_id = check_customer[1].asInt32();
    }

    SACommand check_goods(&con,
                          _TSA("SELECT COUNT(*) FROM Good WHERE name = :1"));
    check_goods << _TSA(goods_name.c_str());
    check_goods.Execute();

    if (check_goods.FetchNext() && check_goods.Field(1).asLong() == 0) {
        std::cerr << "Good: " << goods_name << " does not exist.\n";
        return;
    }

    std::cout << "Pre insert\n";

    std::string time = CurrentDate();

    std::string transactionNum = "TXN" + customer_email + time;

    std::cout << time << "\n";

    try {
        SACommand insert(&con, _TSA("INSERT INTO Transaction (transactionType, "
                                    "time, shippingID, facilityID, "
                                    "customerID, transactionNum) "
                                    "VALUES (:1, :2, :3, :4, :5, :6)"));

        std::string transaction_type_s = std::string(1, transaction_type);

        insert << _TSA(transaction_type_s.c_str()) << _TSA(time.c_str())
               << _TSA(shipping_id) << _TSA(facility_id) << _TSA(customer_id)
               << _TSA(transactionNum.c_str());

        insert.Execute();
    } catch (SAException& e) {
        std::cerr << e.ErrMessage().GetMultiByteChars() << "\n";
        return;
    }
}

void Transaction::GetTransactionByCustomer(SAConnection& con,
                                           const std::string& customer_email) {
    std::string query =
        "SELECT "
        "Transaction.transactionNum, "
        "Transaction.transactionType, "
        "Transaction.time AS transactionTime, "
        "Facility.name AS facilityName, "
        "Region.name AS facilityRegion, "
        "Good.name AS goodsName, "
        "TransactionDetail.quantity AS goodsQuantity, "
        "ShippingMethod.typeID AS shippingMethod, "
        "ShippingCourier.name AS shippingCourier "
        "FROM "
        "Transaction "
        "JOIN Customer ON Transaction.customerID = Customer.ID "
        "JOIN ShippingMethod ON Transaction.shippingID = ShippingMethod.ID "
        "JOIN ShippingCourier ON ShippingMethod.courierID = ShippingCourier.ID "
        "JOIN Facility ON Transaction.facilityID = Facility.ID "
        "JOIN Region ON Facility.regionID = Region.ID "
        "JOIN TransactionDetail ON Transaction.ID = "
        "TransactionDetail.transactionID "
        "JOIN Good ON TransactionDetail.goodID = Good.ID "
        "WHERE Customer.email = ':1' "
        "ORDER BY Transaction.time;";
    SACommand select(&con, query.c_str());
    select << _TSA(customer_email.c_str());
    select.Execute();

    SAString transaction_type;
    SAString transaction_time;
    SAString facility_name;
    SAString facility_region;
    SAString order_number;
    SAString goods_name;
    SAString goods_quantity;
    SAString shipping_type;
    SAString shipping_courier;
    std::cout << "Showing " << select.RowsAffected() << " facilities\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        transaction_type = select[2].asString();
        transaction_time = select[3].asString();
        facility_name = select[4].asString();
        facility_region = select[5].asString();
        order_number = select[6].asString();
        goods_name = select[7].asString();
        goods_quantity = select[8].asString();
        shipping_type = select[9].asString();
        shipping_courier = select[10].asString();

        std::cout << "Transaction Type: "
                  << transaction_type.GetMultiByteChars() << "\n";
        std::cout << "Transaction Time: "
                  << transaction_time.GetMultiByteChars() << "\n";
        std::cout << "Facility: " << facility_name.GetMultiByteChars() << "\n";
        std::cout << "Facility Region: " << facility_region.GetMultiByteChars()
                  << "\n";
        std::cout << "Order Number: " << order_number.GetMultiByteChars()
                  << "\n";
        std::cout << "Goods: " << goods_name.GetMultiByteChars() << "\n";
        std::cout << "Quantity: " << goods_quantity.GetMultiByteChars() << "\n";
        std::cout << "Shipping Type: " << shipping_type.GetMultiByteChars()
                  << "\n";
        std::cout << "Shipping Courier: "
                  << shipping_courier.GetMultiByteChars() << "\n\n";
    }
}

void Transaction::GetTransactionByFacility(SAConnection& con,
                                           const std::string& facility_name) {
    std::string query =
        "SELECT "
        "Transaction.transactionNum, "
        "Transaction.transactionType, "
        "Transaction.time AS transactionTime, "
        "Facility.name AS facilityName, "
        "Region.name AS facilityRegion, "
        "Good.name AS goodsName, "
        "TransactionDetail.quantity AS goodsQuantity, "
        "ShippingMethod.typeID AS shippingMethod, "
        "ShippingCourier.name AS shippingCourier "
        "FROM "
        "Transaction "
        "JOIN Facility ON Transaction.facilityID = Facility.ID "
        "JOIN Region ON Facility.regionID = Region.ID "
        "JOIN ShippingMethod ON Transaction.shippingID = ShippingMethod.ID "
        "JOIN ShippingCourier ON ShippingMethod.courierID = ShippingCourier.ID "
        "JOIN TransactionDetail ON Transaction.ID = "
        "TransactionDetail.transactionID "
        "JOIN Good ON TransactionDetail.goodID = Good.ID "
        "WHERE Facility.name = ':1' "
        "ORDER BY Transaction.time;";
    SACommand select(&con, query.c_str());
    select << _TSA(facility_name.c_str());
    select.Execute();

    SAString transaction_type;
    SAString transaction_time;
    SAString facility_name_sa;
    SAString facility_region;
    SAString order_number;
    SAString goods_name;
    SAString goods_quantity;
    SAString shipping_type;
    SAString shipping_courier;
    std::cout << "Showing " << select.RowsAffected() << " facilities\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        transaction_type = select[2].asString();
        transaction_time = select[3].asString();
        facility_name_sa = select[4].asString();
        facility_region = select[5].asString();
        order_number = select[6].asString();
        goods_name = select[7].asString();
        goods_quantity = select[8].asString();
        shipping_type = select[9].asString();
        shipping_courier = select[10].asString();

        std::cout << "Transaction Type: "
                  << transaction_type.GetMultiByteChars() << "\n";
        std::cout << "Transaction Time: "
                  << transaction_time.GetMultiByteChars() << "\n";
        std::cout << "Facility: " << facility_name_sa.GetMultiByteChars()
                  << "\n";
        std::cout << "Facility Region: " << facility_region.GetMultiByteChars()
                  << "\n";
        std::cout << "Order Number: " << order_number.GetMultiByteChars()
                  << "\n";
        std::cout << "Goods: " << goods_name.GetMultiByteChars() << "\n";
        std::cout << "Quantity: " << goods_quantity.GetMultiByteChars() << "\n";
        std::cout << "Shipping Type: " << shipping_type.GetMultiByteChars()
                  << "\n";
        std::cout << "Shipping Courier: "
                  << shipping_courier.GetMultiByteChars() << "\n\n";
    }
}

//Maybe use std::time or ctime instead of string?
void Transaction::GetTransactionByDateRange(SAConnection& con,
                                            const std::string& start_date,
                                            const std::string& end_date) {
    std::string query =
        "SELECT "
        "Transaction.transactionNum, "
        "Transaction.transactionType, "
        "Transaction.time AS transactionTime, "
        "Facility.name AS facilityName, "
        "Region.name AS facilityRegion, "
        "Good.name AS goodsName, "
        "TransactionDetail.quantity AS goodsQuantity, "
        "ShippingMethod.typeID AS shippingMethod, "
        "ShippingCourier.name AS shippingCourier "
        "FROM "
        "Transaction "
        "JOIN ShippingMethod ON Transaction.shippingID = ShippingMethod.ID "
        "JOIN ShippingCourier ON ShippingMethod.courierID = ShippingCourier.ID "
        "JOIN Facility ON Transaction.facilityID = Facility.ID "
        "JOIN Region ON Facility.regionID = Region.ID "
        "JOIN TransactionDetail ON Transaction.ID = "
        "TransactionDetail.transactionID "
        "JOIN Good ON TransactionDetail.goodID = Good.ID "
        "WHERE Transaction.time BETWEEN :1 AND :2::DATE + INTERVAL '1 DAY' "
        "ORDER BY Transaction.time;";
    SACommand select(&con, query.c_str());
    select << _TSA(start_date.c_str()) << _TSA(end_date.c_str());
    select.Execute();

    SAString transaction_type;
    SAString transaction_time;
    SAString facility_name;
    SAString facility_region;
    SAString order_number;
    SAString goods_name;
    SAString goods_quantity;
    SAString shipping_type;
    SAString shipping_courier;
    std::cout << "Showing " << select.RowsAffected() << " facilities\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        transaction_type = select[2].asString();
        transaction_time = select[3].asString();
        facility_name = select[4].asString();
        facility_region = select[5].asString();
        order_number = select[6].asString();
        goods_name = select[7].asString();
        goods_quantity = select[8].asString();
        shipping_type = select[9].asString();
        shipping_courier = select[10].asString();

        std::cout << "Transaction Type: "
                  << transaction_type.GetMultiByteChars() << "\n";
        std::cout << "Transaction Time: "
                  << transaction_time.GetMultiByteChars() << "\n";
        std::cout << "Facility: " << facility_name.GetMultiByteChars() << "\n";
        std::cout << "Facility Region: " << facility_region.GetMultiByteChars()
                  << "\n";
        std::cout << "Order Number: " << order_number.GetMultiByteChars()
                  << "\n";
        std::cout << "Goods: " << goods_name.GetMultiByteChars() << "\n";
        std::cout << "Quantity: " << goods_quantity.GetMultiByteChars() << "\n";
        std::cout << "Shipping Type: " << shipping_type.GetMultiByteChars()
                  << "\n";
        std::cout << "Shipping Courier: "
                  << shipping_courier.GetMultiByteChars() << "\n\n";
    }
}