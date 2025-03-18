#include "goods.h"
#include <cstring>
#include <iostream>
#include <string>

void Goods::CreateGoods(SAConnection& con, const std::string& name,
                        const std::string& description, const std::string& SKU,
                        const std::string& category) {
    SACommand insert(&con, _TSA("INSERT INTO GOOD (NAME, DESCRIPTION, SKU, "
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

void Goods::SearchGoods(SAConnection& con, const std::string& name) {}

void Goods::ListAllGoods(SAConnection& con) {}

void Goods::GetGoodsVolumeByDate(SAConnection& con,
                                 const std::string& start_date,
                                 const std::string& end_date) {}

void Goods::GetTotalGoodsVolume(SAConnection& con) {}

void Goods::CreateGoodsCategory(SAConnection& con, const std::string& name) {}

void Goods::ListAllGoodsCategories(SAConnection& con) {}

void Goods::GetGoodsWeightByCategory(SAConnection& con,
                                     const std::string& category) {}