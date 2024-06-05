#pragma once

#include <map>
#include <memory>
#include <vector>

#include "simulation_report_entity.h"
#include "../rental/rental.h"

class SimulationReport
{
private:
    std::map<Customer *, std::unique_ptr<ReportEntity>> customerRentals;
    std::map<Vehicle *, std::unique_ptr<ReportEntity>> vehicleUsage;

public:
    void addRentalData(const Rental *rental);
    void addMaintenanceData(Vehicle *vehicle);
    void generateCustomerSummary();
    void generateVehicleSummary();
};