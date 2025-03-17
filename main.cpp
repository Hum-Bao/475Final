#include <stdio.h>
#include <iostream>
#include <map>
#include "customerdriver.h"

#include "SQLAPI/include/SQLAPI.h"

const std::map<int, std::string> APIS = {{1, "Customer APIs"},
                                         {2, "Transaction APIs"},
                                         {3, "Facility APIs"},
                                         {4, "Shipping APIs"},
                                         {5, "Goods APIs"}};

int main(int argc, char* argv[]) {

    SAConnection con;
    try {
        con.Connect(_TSA("baadb"), _TSA("postgres"), _TSA(""),
                    SA_PostgreSQL_Client);
        std::cout << "We are connected!" << "\n";
    } catch (SAException& x) {
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }

    std::cout << "Select API category: \n";
    for (std::pair<int, std::string> temp : APIS) {
        std::cout << temp.first << ". " << temp.second << "\n";
    }
    int option = 0;
    std::cin >> option;

    switch (option) {
        case 1: {
            CustomerDriver::SelectCustomerAPI(con);
            break;
        }
        case 2: {
            //Transaction
            break;
        }
        case 3: {
            //Facility
            break;
        }
        case 4: {
            //Shipping
            break;
        }
        case 5: {
            //Goods
            break;
        }
        default: {
            std::cout << "Not yet implemented\n";
            break;
        }
    }

    return 0;

    /*
    SAConnection con;

    try {
        con.Connect(_TSA("db02"), _TSA("postgres"), _TSA(""),
                    SA_PostgreSQL_Client);
        std::cout << "We are connected!" << "\n";

        SACommand select(&con, _TSA("SELECT * FROM employee"));

        // select << 30;
        select.Execute();

        while (select.FetchNext()) {

            //Non-hardcoded
            std::cout << "Field count: " << select.FieldCount() << "\n";
            for (int count = 1; count <= select.FieldCount(); count++) {
                std::cout << select.Field(count).Name().GetMultiByteChars()
                          << ": "
                          << select[count].asString().GetMultiByteChars()
                          << " ";
            }
            std::cout << "\n\n";

            //Hardcoded
            int sID = select[1].asInt32();
            SAString sNum = select[2].asString();
            SAString sName = select[3].asString();
            SAString sEmail = select[4].asString();
            int sDID = select[5].asInt32();
            SAString sSalary = select[6].asString();
            printf(
                "ID: %10d, Num: %10s, Name: %10s, Email: %20s, Dept.ID: %5d, "
                "Salary: "
                "%s\n",
                sID, sNum.GetMultiByteChars(), sName.GetMultiByteChars(),
                sEmail.GetMultiByteChars(), sDID, sSalary.GetMultiByteChars());
                
        }

        con.Disconnect();
        printf("We are disconnected!\n");
    } catch (SAException& x) {
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }
*/
}