#include "customer.h"
#include <iostream>
#include "SQLAPI/include/SQLAPI.h"

void Customer::CreateCustomer(SAConnection& con, const std::string& name,
                              const std::string& email,
                              const std::string& phone) {
    try {
        SACommand insert(&con, _TSA("INSERT INTO CUSTOMER (NAME, EMAIL, PHONE) "
                                    "VALUES (:1, :2, :3)"));

        insert << _TSA(name.c_str()) << _TSA(email.c_str())
               << _TSA(phone.c_str());
        insert.Execute();
    } catch (SAException& e) {
        std::cerr << e.ErrMessage().GetMultiByteChars() << "\n";
        return;
    }

    std::cout << "Successfully added customer with name: " << name
              << " email: " << email << " and phone: " << phone << "\n";
}

void Customer::UpdateCustomer(SAConnection& con, const std::string& email,
                              const std::string& change_field,
                              const std::string& new_val) {

    //Get customer id
    SACommand select(&con, _TSA("SELECT ID FROM Customer WHERE email = :1"));
    select << _TSA(email.c_str());
    select.Execute();

    if (select.FetchNext()) {
        int id = select.Field(1).asLong();

        //Update record
        std::string command =
            "UPDATE Customer SET " + change_field + "= :1 WHERE ID = :2";
        SACommand update(&con, _TSA(command.c_str()));
        update << _TSA(new_val.c_str()) << id;
        update.Execute();
    } else {
        std::cerr << "Customer with email: " << email << " not found.\n";
    }

    std::cout << "Successfully updated customer\n";
}

void Customer::ViewCustomer(SAConnection& con, const std::string& email) {
    SACommand select(&con, _TSA("SELECT * FROM CUSTOMER WHERE EMAIL = :1"));
    select << _TSA(email.c_str());
    select.Execute();

    if (select.FetchNext()) {
        //Select[1] is the id
        SAString select_name = select[2].asString();
        SAString select_email = select[3].asString();
        SAString select_phone = select[4].asString();
        std::cout << "Name: " << select_name.GetMultiByteChars() << "\n";
        std::cout << "  Email: " << select_email.GetMultiByteChars() << "\n";
        std::cout << "  Phone: " << select_phone.GetMultiByteChars() << "\n";
    }
}

void Customer::ListAllCustomers(SAConnection& con) {
    SACommand select(&con, _TSA("SELECT * FROM CUSTOMER"));
    select.Execute();

    SAString select_name;
    SAString select_email;
    SAString select_phone;
    std::cout << "Showing " << select.RowsAffected() << " customers:\n";
    while (select.FetchNext()) {
        //Select[1] is the id
        select_name = select[2].asString();
        select_email = select[3].asString();
        select_phone = select[4].asString();
        std::cout << "Name: " << select_name.GetMultiByteChars() << "\n";
        std::cout << "  Email: " << select_email.GetMultiByteChars() << "\n";
        std::cout << "  Phone: " << select_phone.GetMultiByteChars() << "\n";
        std::cout << "\n";
    }
}