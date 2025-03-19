#include "transaction.h"
#include <iostream>
#include "SQLAPI/include/SQLAPI.h"

void Transaction::CreateTransaction(SAConnection& con,
                                    const char& transaction_type,
                                    const std::string& customer_email,
                                    const std::string& facility_name,
                                    const std::string& shipping_method_type,
                                    const std::string& shipping_courier,
                                    const std::string& goods_name,
                                    const std::string& goods_quantity) {

    SACommand check_shipping_method(
        &con, _TSA("SELECT COUNT(*) FROM SHIPPING_METHOD WHERE TYPE = :1"));
    check_shipping_method << _TSA(shipping_method_type.c_str());
    check_shipping_method.Execute();

    if (check_shipping_method.FetchNext() &&
        check_shipping_method.Field(1).asLong() == 0) {
        std::cerr << "Shipping type: " << shipping_method_type
                  << " with courier: " << shipping_courier
                  << " does not exist.\n";
        return;
    }

    SACommand check_goods(&con,
                          _TSA("SELECT COUNT(*) FROM GOODS WHERE NAME = :1"));
    check_goods << _TSA(goods_name.c_str());
    check_goods.Execute();

    if (check_goods.FetchNext() && check_goods.Field(1).asLong() == 0) {
        std::cerr << "Good: " << goods_name << " does not exist.\n";
        return;
    }

    SACommand insert(&con,
                     _TSA("INSERT INTO TRANSACTION (TRANSACTION_TYPE, "
                          "CUSTOMER_EMAIL, FACILITY_NAME, SHIPPING_METHOD, "
                          "SHIPPING_COURIER, GOODS_NAME, GOODS_QUANTITY) "
                          "VALUES (:1, :2, :3, :4, :5, :6, :7)"));

    insert << transaction_type << _TSA(customer_email.c_str())
           << _TSA(facility_name.c_str()) << _TSA(shipping_method_type.c_str())
           << _TSA(shipping_courier.c_str()) << _TSA(goods_name.c_str())
           << _TSA(goods_quantity.c_str());

    insert.Execute();
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
                                           std::string facility_name) {
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