#include <iostream>
#include "customerdriver.h"
#include "facilitydriver.h"
#include "goodsdriver.h"
#include "shippingdriver.h"

#include "SQLAPI/include/SQLAPI.h"
#include "transactiondriver.h"

const int NUM_APIS = 6;

const std::array<std::pair<int, std::string>, NUM_APIS> APIS = {
    {{1, "Customer APIs"},
     {2, "Transaction APIs"},
     {3, "Facility APIs"},
     {4, "Shipping APIs"},
     {5, "Goods APIs"},
     {6, "Exit"}}};

int main() {

    SAConnection con;
    try {
        con.Connect(_TSA("baadb"), _TSA("postgres"), _TSA(""),
                    SA_PostgreSQL_Client);
        std::cout << "We are connected!" << "\n";
    } catch (SAException& x) {
        con.Rollback();
        std::cerr << x.ErrText().GetMultiByteChars() << "\n";
        return -1;
    }

    while (true) {

        std::cout << "Select API category: \n";
        for (const std::pair<int, std::string>& temp : APIS) {
            std::cout << temp.first << ". " << temp.second << "\n";
        }
        int option = 0;

        std::cin >> option;

        while (!std::cin.good()) {
            std::cout.clear();
            std::cin.clear();
            std::cin.ignore();
            std::cin >> option;
        }

        switch (option) {
            case 1: {
                CustomerDriver::SelectCustomerAPI(con);
                break;
            }
            case 2: {
                TransactionDriver::SelectTransactionAPI(con);
                break;
            }
            case 3: {
                FacilityDriver::SelectFacilityAPI(con);
                break;
            }
            case 4: {
                ShippingDriver::SelectShippingAPI(con);
                //Shipping
                break;
            }
            case 5: {
                GoodsDriver::SelectGoodsAPI(con);
                break;
            }
            case 6: {
                //Exit
                con.Disconnect();
                return 0;
            }
            default: {
                std::cout << "Invalid API option: " << option << "\n";
                break;
            }
        }
        std::cout << "\n";
    }

    return -1;

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