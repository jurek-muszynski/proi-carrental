#include "simulation_report_entity.h"

void ReportEntity::addCost(double amount)
{
    totalCost += amount;
}

void ReportEntity::addRentalCount()
{
    rentalCount++;
}

void CustomerData::addDuration(double duration)
{
    totalDuration += duration;
}

std::string CustomerData::generateReport() const
{
    std::stringstream ss;
    ss << "Total Rentals: " << rentalCount << "\n";
    ss << "Total Cost: " << std::fixed << std::setprecision(2) << totalCost << "$\n";
    ss << "Total Rental Duration: " << totalDuration << " hours\n";
    ss << "Average Rental Duration: " << totalDuration / rentalCount << " hours\n";
    return ss.str();
}

void VehicleData::addMaintenanceCount()
{
    maintenanceCount++;
}

std::string VehicleData::generateReport() const
{
    std::stringstream ss;
    ss << "Total Rentals: " << rentalCount << "\n";
    ss << "Total Maintenance Count: " << maintenanceCount << "\n";
    return ss.str();
}
