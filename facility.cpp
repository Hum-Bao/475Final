#include "facility.h"
#include <iostream>
#include "SQLAPI/include/SQLAPI.h"
#include <iostream>

void Facility::CreateFacility(SAConnection& con, std::string name, std::string region){
      SACommand insert(
        &con,
        _TSA("INSERT INTO Facility (NAME, REIGON) VALUES (:1, :2)"));

        insert << _TSA(name.c_str()) << _TSA(reigon.c_str());
        insert.Execute();
        //for testing purposes|| where will we actually add the success conformation messages???
        cout << "facility successfully created" << endl; 
}

void Facility::UpdateFacility(SAConnection& con, std::string name, std::string update_field){
  
}

void Facility::ListAllFacilities(SAConnection& con){
  
}
