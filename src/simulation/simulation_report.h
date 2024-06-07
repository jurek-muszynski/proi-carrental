#pragma once

#include <map>
#include <memory>
#include <vector>

#include "simulation_report_entity.h"
#include "../rental/rental.h"

class SimulationReport
{
private:
    std::map<std::shared_ptr<Customer>, std::unique_ptr<ReportEntity>> customerRentals;
    std::map<std::shared_ptr<Vehicle>, std::unique_ptr<ReportEntity>> vehicleUsage;

public:
    void addRentalData(std::shared_ptr<Rental>);
    void addMaintenanceData(std::shared_ptr<Vehicle>);
    void addAccidentData(std::shared_ptr<Vehicle>);
    void generateCustomerSummary();
    void generateVehicleSummary();
};