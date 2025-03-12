#include <stdio.h>
#include <iostream>

#include "SQLAPI/include/SQLAPI.h"

int main(int argc, char* argv[]) {
    SAConnection con;

    try {
        con.Connect(_TSA("db02"), _TSA("postgres"), _TSA(""),
                    SA_PostgreSQL_Client);
        std::cout << "We are connected!" << "\n";

        /*
        The rest of the tutorial goes here!
        */

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

            /*
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
                */
        }

        con.Disconnect();
        printf("We are disconnected!\n");
    } catch (SAException& x) {
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }

    return 0;
}