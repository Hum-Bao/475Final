#include "facility.h"
#include <iostream>
#include "SQLAPI/include/SQLAPI.h"

void Facility::CreateFacility(SAConnection& con, const std::string& name,
                              const std::string& region) {
    SACommand insert(
        &con, _TSA("INSERT INTO Facility (NAME, REIGON) VALUES (:1, :2)"));

    insert << _TSA(name.c_str()) << _TSA(region.c_str());
    insert.Execute();
    //for testing purposes|| where will we actually add the success conformation messages???
    std::cout << "facility successfully created" << "\n";
}

void Facility::UpdateFacility(SAConnection& con, const std::string& name,
                              const std::string& update_field,
                              const std::string& new_val) {
    SACommand select(&con, _TSA("SELECT ID FROM FACILITY WHERE NAME = :1"));
    select << _TSA(name.c_str());
    select.Execute();

    if (select.FetchNext()) {
        int id = select.Field(1).asLong();

        std::string command =
            "UPDATE FACILITY SET " + update_field + "= :1 WHERE ID = :2";
        SACommand update(&con, _TSA(command.c_str()));
        update << _TSA(new_val.c_str()) << id;
        update.Execute();
    } else {
        std::cerr << "Facility with name: " << name << " not found.\n";
    }
}

void Facility::ListAllFacilities(SAConnection& con) {
    SACommand select(&con, _TSA("SELECT * FROM FACILITY"));
    select.Execute();

    SAString select_name;
    SAString select_reigon;
    std::cout << "Showing " << select.RowsAffected() << " facilities\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        select_name = select[2].asString();
        select_reigon = select[3].asString();
        std::cout << "Name: " << select_name.GetMultiByteChars() << "\n";
        std::cout << "  Email: " << select_reigon.GetMultiByteChars() << "\n";
        std::cout << "\n";
    }
}
