#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include "src/fleet/fleet_management.h"
#include "src/simulation/simulation.h"

int main()
{
    // SAMPLE DEMO
    Simulation sim;
    // FleetManagement fleet("data/vehicles.json");

    // std::cout << fleet << std::endl;
    std::cout << sim.getDateTime() << std::endl;
    for (int i = 0; i < 20; ++i)
    {
        sim.passTime();
        std::cout << sim.getDateTime() << std::endl;
    }
    return 0;
}