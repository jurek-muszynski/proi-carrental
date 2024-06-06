#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include "src/fleet/fleet_management.h"
#include "src/customer/customer_management.h"
#include "src/rental/rental_management.h"
#include "src/simulation/simulation.h"

int main()
{
    // SAMPLE DEMO -> pass the absolute path to the data folder in case it throws a json file error

    RentalManagement *rm = new RentalManagement();
    CustomerManagement *cm = new CustomerManagement();
    FleetManagement *fm = new FleetManagement();

    Simulation sim(10, cm, fm, rm, "/home/mlewko/proi/24l-proi-lewko-muszynski/data");
    sim.run();
    return 0;
}