#include <iostream>
#include "src/customer/customer.h"
#include "src/fleet/fleet_management.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "src/vehicle/vehicle.h"
#include <string>

int main()
{
    // SAMPLE DEMO
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900; // years since 1900
    birthDate.tm_mon = 12 - 1;       // months since January (0-11)
    birthDate.tm_mday = 25;          // day of the month (1-31)

    Address address("1", "123 Main St", "New York", "NY", "10001");

    Customer customer("1", "John", "Doe", birthDate, "Male", "johndoe@example.com", "1234567890", address);

    FleetManagement fleet("data/vehicles.json");

    std::cout << fleet << std::endl;
    return 0;
}