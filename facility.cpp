#include "facility.h"
#include <iostream>
#include <map>
#include "SQLAPI/include/SQLAPI.h"

void Facility::CreateFacility(SAConnection& con, const std::string& name,
                              const std::string& region) {
    std::map<std::string, int> regions = std::map<std::string, int>();
    SACommand get_regions(&con, _TSA("SELECT * FROM REGION"));
    get_regions.Execute();
    while (get_regions.FetchNext()) {
        regions[get_regions[2].asString().GetMultiByteChars()] =
            get_regions[1].asInt32();
    }
    try {
        SACommand insert(
            &con,
            _TSA("INSERT INTO Facility (name, regionID) VALUES (:1, :2)"));

        insert << _TSA(name.c_str()) << _TSA(regions[region]);
        insert.Execute();
    } catch (SAException& e) {
        std::cerr << e.ErrMessage().GetMultiByteChars() << "\n";
        return;
    }
    std::cout << "Facility: " << name << " created in region: " << region
              << "\n";
}

void Facility::UpdateFacility(SAConnection& con, const std::string& name,
                              const std::string& update_field,
                              const std::string& new_val) {
    SACommand select(&con, _TSA("SELECT ID FROM FACILITY WHERE NAME = :1"));
    select << _TSA(name.c_str());
    select.Execute();

    try {
        if (select.FetchNext()) {
            int facility_id = select[1].asInt32();

            std::string command =
                "UPDATE FACILITY SET " + update_field + " = :1 WHERE ID = :2";
            SACommand update(&con, _TSA(command.c_str()));
            if (update_field == "REGIONID") {
                std::map<std::string, int> regions =
                    std::map<std::string, int>();
                SACommand get_regions(&con, _TSA("SELECT * FROM REGION"));
                get_regions.Execute();
                while (get_regions.FetchNext()) {
                    regions[get_regions[2].asString().GetMultiByteChars()] =
                        get_regions[1].asInt32();
                }
                update << _TSA(regions[new_val]) << _TSA(facility_id);
            } else {
                update << _TSA(new_val.c_str()) << _TSA(facility_id);
            }
            update.Execute();
        } else {
            std::cerr << "Facility with name: " << name << " not found.\n";
        }
    } catch (SAException& e) {
        std::cerr << e.ErrMessage().GetMultiByteChars() << "\n";
        return;
    }
    std::cout << "Facility successfully updated\n";
}

void Facility::ListAllFacilities(SAConnection& con) {
    std::map<int, std::string> regions = std::map<int, std::string>();
    SACommand get_regions(&con, _TSA("SELECT * FROM REGION"));
    get_regions.Execute();
    while (get_regions.FetchNext()) {
        regions[get_regions[1].asInt32()] = get_regions[2].asString();
    }

    SACommand select(&con, _TSA("SELECT * FROM FACILITY"));
    select.Execute();

    SAString select_name;
    int select_region = 0;
    std::cout << "Showing " << select.RowsAffected() << " facilities\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        select_name = select[2].asString();
        select_region = select[3].asInt32();
        std::cout << "Name: " << select_name.GetMultiByteChars() << "\n";
        std::cout << "  Region: " << regions[select_region] << "\n";
        std::cout << "\n";
    }
}

void Facility::ListAllRegions(SAConnection& con) {
    SACommand get_regions(&con, _TSA("SELECT * FROM REGION"));
    get_regions.Execute();
    SAString region_name;
    std::cout << "Showing " << get_regions.RowsAffected() << " regions:\n";
    while (get_regions.FetchNext()) {
        region_name = get_regions[2].asString();
        std::cout << region_name.GetMultiByteChars() << "\n";
    }
}
