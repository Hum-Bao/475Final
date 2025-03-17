#ifndef CUSTOMERDRIVER_H
#define CUSTOMERDRIVER_H

#include <array>
#include <string>

class CustomerDriver {
    public:
        static void SelectCustomerAPI();

    private:
        const static std::array<std::pair<int, std::string>, 4> METHODS;
};

#endif
