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

    std::string numberOfSimulations;
    int iterations = 10;

    while (true)
    {
        std::cout << "Enter the number of simulations: ";
        std::cin >> numberOfSimulations;

        try
        {
            iterations = std::stoi(numberOfSimulations);
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid input" << std::endl;
            continue;
        }

        if (iterations > 0)
        {
            break;
        }
        else
        {
            std::cout << "Number of simulations must be greater than 0" << std::endl;
        }
    }

    std::cout << std::endl;

    Simulation sim(iterations, "data");
    sim.run();

    return 0;
}