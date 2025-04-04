#include "simulation_report.h"

void SimulationReport::addRentalData(std::shared_ptr<Rental> rental)
{
    std::shared_ptr<Customer> customer = rental->getCustomer();
    std::shared_ptr<Vehicle> vehicle = rental->getVehicle();

    double rentalCost = rental->calculateCost();

    if (customerRentals.find(customer) == customerRentals.end())
    {
        customerRentals[customer] = std::make_unique<CustomerData>();
    }
    CustomerData *customerData = static_cast<CustomerData *>(customerRentals[customer].get());
    customerData->addRentalCount();
    customerData->addCost(rentalCost);
    customerData->addDuration(rental->getDuration());

    if (vehicleUsage.find(vehicle) == vehicleUsage.end())
    {
        vehicleUsage[vehicle] = std::make_unique<VehicleData>();
    }
    VehicleData *vehicleData = static_cast<VehicleData *>(vehicleUsage[vehicle].get());
    vehicleData->addRentalCount();
    vehicleData->addCost(rentalCost);
}

void SimulationReport::addMaintenanceData(std::shared_ptr<Vehicle> vehicle)
{
    if (vehicleUsage.find(vehicle) == vehicleUsage.end())
    {
        vehicleUsage[vehicle] = std::make_unique<VehicleData>();
    }
    VehicleData *vehicleData = static_cast<VehicleData *>(vehicleUsage[vehicle].get());
    vehicleData->addMaintenanceCount();
}

void SimulationReport::addAccidentData(std::shared_ptr<Vehicle> vehicle)
{
    if (vehicleUsage.find(vehicle) == vehicleUsage.end())
    {
        vehicleUsage[vehicle] = std::make_unique<VehicleData>();
    }
    VehicleData *vehicleData = static_cast<VehicleData *>(vehicleUsage[vehicle].get());
    vehicleData->addAccidentCount();
}

void SimulationReport::generateCustomerSummary()
{
    std::stringstream ss;
    ss << "\nCustomer Summary Report\n";
    ss << "-------------------------\n";

    for (const auto &entry : customerRentals)
    {
        const std::shared_ptr<Customer> customer = entry.first;
        const CustomerData *data = static_cast<CustomerData *>(entry.second.get());

        ss << "Customer: " << *customer << "\n";
        ss << data->generateReport();
        ss << "-------------------------\n";
    }

    std::cout << ss.str();
}

void SimulationReport::generateVehicleSummary()
{
    std::stringstream ss;
    ss << "\nVehicle Summary Report\n";
    ss << "--------------------\n";

    for (const auto &entry : vehicleUsage)
    {
        const std::shared_ptr<Vehicle> vehicle = entry.first;
        const VehicleData *data = static_cast<VehicleData *>(entry.second.get());

        ss << "Vehicle: " << vehicle->getMake() << " License Plate: " << vehicle->getLicensePlate() << "\n";
        ss << data->generateReport();
        if (vehicle->getMileage() > 0)
            ss << "Total Mileage: " << std::fixed << std::setprecision(2) << vehicle->getMileage() << " km\n";
        ss << "--------------------\n";
    }

    std::cout << ss.str();
}