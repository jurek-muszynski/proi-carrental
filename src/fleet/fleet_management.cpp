#include "fleet_management.h"

FleetManagement::FleetManagement(std::vector<Vehicle *> vehicles)
    : vehicles(vehicles)
{
}

FleetManagement::~FleetManagement()
{
    for (Vehicle *vehicle : vehicles)
    {
        delete vehicle;
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
    return nullptr;
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

bool FleetManagement::addVehicle(Vehicle *vehicle)
{
    auto it = std::find_if(vehicles.begin(), vehicles.end(), [&](Vehicle *v)
                           { return v->getId() == vehicle->getId(); });

    if (it == vehicles.end())
    {
        vehicles.push_back(vehicle);
        return true;
    }

    return false;
}

bool FleetManagement::removeVehicle(const std::string id)
{
    auto it = std::find_if(vehicles.begin(), vehicles.end(), [&](Vehicle *vehicle)
                           { return vehicle->getId() == id; });

    if (it != vehicles.end())
    {
        delete *it;
        vehicles.erase(it);
        return true;
    }

    return false;
}

std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet)
{
    for (Vehicle *vehicle : fleet.vehicles)
    {
        os << *vehicle << std::endl;
    }
    return os;
}
