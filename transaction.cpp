#include "transaction.h"
#include <iostream>
#include "SQLAPI/include/SQLAPI.h"
#include <map>
/*
Transaction::Transaction(){
    try {
        con.Connect("your_database", "your_username", "your_password", SA_MySQL_Client);
    } catch (SAException &ex) {
        std::cerr << "Database connection error: " << ex.ErrText().GetMultiByteChars() << std::endl;
    }
}*/
void Transaction::CreateTransaction(char transaction_type,
                               std::string customer_email,
                               std::string facility_name,
                               std::string shipping_method_type,
                               std::string shipping_courier,
                               std::string goods_name,
                               std::string goods_quantity){
                               }

void Transaction::GetTransactionByCustomer(std::string customer_email){
    try {
        SACommand select(&con, "SELECT * FROM Transactions WHERE customer_email = :1");
        select.Param(1).setAsString() = customer_email.c_str();

        select.Execute();
        
        while (select.FetchNext()) {
            std::cout << "Transaction ID: " << select.Field("transaction_id").asLong() << "\n";
            std::cout << "Customer Email: " << select.Field("customer_email").asString().GetMultiByteChars() << "\n";
            std::cout << "Facility Name: " << select.Field("facility_name").asString().GetMultiByteChars() << "\n";
            std::cout << "Goods Name: " << select.Field("goods_name").asString().GetMultiByteChars() << "\n";
            std::cout << "-------------------------------\n";
        }
    } catch (SAException &ex) {
        std::cerr << "Error fetching transactions: " << ex.ErrText().GetMultiByteChars() << std::endl;
    }
}

void Transaction::GetTransactionByFacility(std::string facility_name){
        try {
        SACommand select(&con, "SELECT * FROM Transactions WHERE facility_name = :1");
        select.Param(1).setAsString() = facility_name.c_str();

        select.Execute();

        while (select.FetchNext()) {
            std::cout << "Transaction ID: " << select.Field("transaction_id").asLong() << "\n";
            std::cout << "Customer Email: " << select.Field("customer_email").asString().GetMultiByteChars() << "\n";
            std::cout << "Facility Name: " << select.Field("facility_name").asString().GetMultiByteChars() << "\n";
            std::cout << "Goods Name: " << select.Field("goods_name").asString().GetMultiByteChars() << "\n";
            std::cout << "-------------------------------\n";
        }
    } catch (SAException &ex) {
        std::cerr << "Error fetching transactions by facility: " << ex.ErrText().GetMultiByteChars() << std::endl;
    }
}

        //Maybe use std::time or ctime instead of string?
void Transaction::GetTransactionByDateRange(std::string start_date, std::string end_date){
    try {
        SACommand select(&con, 
            "SELECT * FROM Transactions WHERE transaction_date BETWEEN :1 AND :2");
        
        select.Param(1).setAsString() = start_date.c_str();
        select.Param(2).setAsString() = end_date.c_str();

        select.Execute();

        while (select.FetchNext()) {
            std::cout << "Transaction ID: " << select.Field("transaction_id").asLong() << "\n";
            std::cout << "Transaction Date: " << select.Field("transaction_date").asString().GetMultiByteChars() << "\n";
            std::cout << "Goods Name: " << select.Field("goods_name").asString().GetMultiByteChars() << "\n";
            std::cout << "-------------------------------\n";
        }
    } catch (SAException &ex) {
        std::cerr << "Error fetching transactions by date range: " << ex.ErrText().GetMultiByteChars() << std::endl;
    }
}