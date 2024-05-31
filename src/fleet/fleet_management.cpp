#include "fleet_management.h"

FleetManagement::FleetManagement(std::vector<Vehicle *> vehicles)
    : vehicles(vehicles)
{
}

FleetManagement::FleetManagement(const std::string &filePath)
{
    loadVehiclesFromJson(filePath);
}

void FleetManagement::addVehicle(Vehicle *vehicle)
{
    vehicles.push_back(vehicle);
}

void FleetManagement::removeVehicle(const std::string id)
{
    for (int i = 0; i < vehicles.size(); i++)
    {
        if (vehicles[i]->getId() == id)
        {
            delete vehicles[i];
            vehicles.erase(vehicles.begin() + i);
            break;
        }
    }
}

Vehicle *FleetManagement::getVehicle(const std::string id) const
{
    for (Vehicle *vehicle : vehicles)
    {
        if (vehicle->getId() == id)
        {
            return vehicle;
        }
    }
    return nullptr; // Zwraca nullptr, jeśli nie znaleziono pojazdu
}

std::vector<Vehicle *> FleetManagement::getAvailableVehicles()
{
    std::vector<Vehicle *> availableVehicles;
    for (Vehicle *vehicle : vehicles)
    {
        if (vehicle->getAvailabilityStatus())
        {
            availableVehicles.push_back(vehicle);
        }
    }
    return availableVehicles;
}

void FleetManagement::loadVehiclesFromJson(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        throw std::runtime_error("Cannot open json file");

    json source = json::parse(file);

    for (const auto &item : source)
    {
        std::string id = item["id"];
        std::string licensePlate = item["licensePlate"];
        std::string make = item["make"];
        std::string model = item["model"];
        int year = item["year"];
        std::string color = item["color"];
        std::string transmissionType = item["transmissionType"];
        std::string fuelType = item["fuelType"];
        int seatingCapacity = item["seatingCapacity"];
        bool availabilityStatus = item["availabilityStatus"];
        double rentalRates = item["rentalRates"];

        addVehicle(new Vehicle(id, licensePlate, make, model, year, color, transmissionType,
                               fuelType, seatingCapacity, availabilityStatus, rentalRates));
    }
}

std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet)
{
    for (Vehicle *vehicle : fleet.vehicles)
    {
        os << *vehicle << std::endl;
    }
    return os;
}

FleetManagement::~FleetManagement()
{
    for (Vehicle *vehicle : vehicles)
    {
        delete vehicle;
    }
}
