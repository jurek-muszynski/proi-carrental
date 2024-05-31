#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include "src/fleet/fleet_management.h"
#include "src/simulation/simulation.h"

using namespace date;

int main()
{
    // SAMPLE DEMO
    Simulation sim;
    FleetManagement fleet("data/vehicles.json");

    // std::cout << fleet << std::endl;
    std::cout << sim.getDateTime() << std::endl;
    return 0;
}