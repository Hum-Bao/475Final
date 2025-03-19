#include "goods.h"
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include "SQLAPI/include/SQLAPI.h"

void Goods::CreateGoods(SAConnection& con, const std::string& name,
                        const std::string& description, const std::string& SKU,
                        const std::string& category) {
    SACommand insert(&con, _TSA("INSERT INTO Good (NAME, DESCRIPTION, SKU, "
                                "CATEGORYID) VALUES (:1, :2, :3, :4)"));

    insert << _TSA(name.c_str()) << _TSA(description.c_str())
           << _TSA(SKU.c_str());

    std::string command =
        "SELECT id FROM GoodCategory WHERE name = '" + category + "'";

    SACommand select_category(&con, _TSA(command.c_str()));
    select_category.Execute();
    if (select_category.FetchNext()) {
        int category_id = select_category[1];
        insert << _TSA(category_id);
        insert.Execute();
    } else {
        std::cerr
            << "Category: " << category
            << " does not exist. Please add the category and then try again\n";
    }
}

void Goods::UpdateGoods(SAConnection& con, const std::string& SKU,
                        const std::string& change_field, std::string new_val) {

    //Get Good id
    SACommand select(&con, _TSA("SELECT ID FROM SHIPPING WHERE SKU = :1"));
    select << _TSA(SKU.c_str());
    select.Execute();

    if (select.FetchNext()) {
        int id = select.Field(1).asLong();

        if (change_field == "CATEGORYID") {
            std::string command =
                "SELECT id FROM GoodCategory WHERE name = '" + new_val + "'";
            SACommand select_category(&con, _TSA(command.c_str()));
            select_category.Execute();
            if (select_category.FetchNext()) {
                new_val = select_category[1].asString();
            } else {
                std::cerr << "Category: " << new_val
                          << " does not exist. Please add the category and "
                             "then try again\n";
            }
        }

        //Update record
        std::string command =
            "UPDATE GOOD SET " + change_field + "= :1 WHERE ID = :2";
        SACommand update(&con, _TSA(command.c_str()));
        update << _TSA(new_val.c_str()) << id;
        update.Execute();
    } else {
        std::cerr << "SKU: " << SKU << " not found.\n";
    }
}

void Goods::SearchGoods(SAConnection& con, const std::string& name) {
    std::string command =
        "SELECT * FROM Good WHERE name ILIKE '%" + name + "%'";
    SACommand search(&con, _TSA(command.c_str()));
    search.Execute();
    std::cout << "Showing " << search.RowsAffected() << " goods:\n";
    if (search.RowsAffected() != 0) {
        std::map<int, std::string> categories = std::map<int, std::string>();
        SACommand select_categories(&con, _TSA("SELECT * FROM GoodCategory"));
        select_categories.Execute();

        while (select_categories.FetchNext()) {
            categories[select_categories[1].asInt32()] =
                select_categories[2].asString();
        }

        SAString select_name;
        SAString select_description;
        SAString select_SKU;
        while (search.FetchNext()) {
            //Select[1] is the id
            select_name = search[2].asString();
            select_description = search[3].asString();
            select_SKU = search[4].asString();
            std::cout << "Name: " << select_name.GetMultiByteChars() << "\n";
            std::cout << "  Description: "
                      << select_description.GetMultiByteChars() << "\n";
            std::cout << "  SKU: " << select_SKU.GetMultiByteChars() << "\n";
            std::cout << "  Category: " << categories[search[5].asInt32()];
            std::cout << "\n";
        }
    }
}

void Goods::ListAllGoods(SAConnection& con) {
    std::map<int, std::string> categories = std::map<int, std::string>();

    SACommand select_categories(&con, _TSA("SELECT * FROM GoodCategory"));
    select_categories.Execute();

    while (select_categories.FetchNext()) {
        categories[select_categories[1].asInt32()] =
            select_categories[2].asString();
    }

    SACommand select(&con, _TSA("SELECT * FROM Good"));
    select.Execute();

    SAString select_name;
    SAString select_description;
    SAString select_SKU;
    std::cout << "Showing " << select.RowsAffected() << " goods\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        select_name = select[2].asString();
        select_description = select[3].asString();
        select_SKU = select[4].asString();
        std::cout << "Name: " << select_name.GetMultiByteChars() << "\n";
        std::cout << "  Description: " << select_description.GetMultiByteChars()
                  << "\n";
        std::cout << "  SKU: " << select_SKU.GetMultiByteChars() << "\n";
        std::cout << "  Category: " << categories[select[5].asInt32()];
        std::cout << "\n";
    }
}

void Goods::GetGoodsVolumeByDate(SAConnection& con,
                                 const std::string& start_date,
                                 const std::string& end_date) {
    std::string command = "SELECT SUM(quantity) FROM TransactionDetail ";
    command +=
        "JOIN Transaction ON TransactionDetail.transactionid = Transaction.id ";
    command += "WHERE Transaction.time BETWEEN '" + start_date + "' AND '" +
               end_date + "'::DATE + INTERVAL '1 DAY'";
    SACommand select(&con, command.c_str());
    select.Execute();
    if (select.FetchNext()) {
        std::cout << select[1].asInt32() << " units of goods shipped between "
                  << start_date << " and " << end_date << "\n";
    }
}

void Goods::GetTotalGoodsVolume(SAConnection& con) {
    SACommand select(&con, "SELECT SUM(quantity) FROM TransactionDetail");
    select.Execute();
    if (select.FetchNext()) {
        std::cout << select[1].asInt32() << " units of goods shipped total\n";
    }
}

void Goods::CreateGoodsCategory(SAConnection& con, const std::string& name) {
    SACommand insert(&con, _TSA("INSERT INTO GoodCategory (NAME) VALUES (:1)"));
    insert << _TSA(name.c_str());
    try {
        insert.Execute();
    } catch (SAException& e) {
        std::string error_message = e.ErrText().GetMultiByteChars();
        if (error_message.find("already exists") != std::string::npos) {
            std::cerr << "Category: " << name
                      << " not added as it already exists.\n";
        } else {
            std::cerr << "Unknown error occurred while attempting to add new "
                         "category: "
                      << name << "\n";
        }
    }
}

void Goods::ListAllGoodsCategories(SAConnection& con) {
    SACommand select_categories(&con, _TSA("SELECT * FROM GoodCategory"));
    select_categories.Execute();

    std::cout << "Showing " << select_categories.RowsAffected()
              << " categories:\n";
    while (select_categories.FetchNext()) {
        std::cout << select_categories[2].asString().GetMultiByteChars()
                  << "\n";
    }
}

void Goods::GetGoodsWeightByCategory(SAConnection& con,
                                     const std::string& category) {

    std::map<std::string, int> categories = std::map<std::string, int>();

    SACommand select_categories(&con, _TSA("SELECT * FROM GoodCategory"));
    select_categories.Execute();

    while (select_categories.FetchNext()) {
        categories[select_categories[2].asString().GetMultiByteChars()] =
            select_categories[1].asInt32();
    }

    std::string command =
        "SELECT SUM(TransactionDetail.weight) FROM TransactionDetail ";
    command += "JOIN Good ON TransactionDetail.goodid = Good.id ";
    command += "JOIN GoodCategory ON Good.categoryID = GoodCategory.id ";
    command += "WHERE GoodCategory.id = '" +
               std::to_string(categories[category]) + "'";

    SACommand select(&con, _TSA(command.c_str()));
    select.Execute();

    if (select.FetchNext()) {
        std::cout << select[1].asDouble() << "kgs of " << category
                  << " shipped total\n";
    }
}