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

    FleetManagement fleet("data/vehicles.json");

    std::cout << fleet << std::endl;
    return 0;
}