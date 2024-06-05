#include "simulation_report.h"

void SimulationReport::addRentalData(const Rental *rental)
{
    Customer* customer = rental->getCustomer();

    CustomerData &data = customerRentals[customer];
    data.rentalCount++;
    data.totalCost += rental->calculateCost();
    data.totalDuration += rental->getDuration();
}

void SimulationReport::generateSummary() const
{
    std::stringstream ss;
    ss << "\nSimulation Summary Report\n";
    ss << "-------------------------\n";

    for (const auto &entry : customerRentals)
    {
        const Customer *customer = entry.first;
        const CustomerData &data = entry.second;

        ss << "Customer ID: " << *customer << "\n";
        ss << "Total Rentals: " << data.rentalCount << "\n";
        ss << "Total Cost: " << std::fixed << std::setprecision(2) << data.totalCost << "$\n";
        ss << "Total Rental Duration: " << data.totalDuration << " hours\n";
        ss << "Average Rental Duration: " << data.totalDuration / data.rentalCount << " hours\n";
        ss << "-------------------------\n";
    }

    std::cout << ss.str();
}