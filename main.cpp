#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include "src/fleet/fleet_management.h"
#include "src/simulation/simulation.h"

int main()
{
    // SAMPLE DEMO -> pass the absolute path to the data folder in case it throws a json file error
    Simulation sim(3, "data");
    srand(time(0));
    sim.run();
    return 0;
}