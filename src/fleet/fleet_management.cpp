#include "fleet_management.h"

FleetManagement::FleetManagement(std::vector<std::shared_ptr<Vehicle>> vehicles)
    : vehicles(vehicles)
{
}

FleetManagement::~FleetManagement()
{
    vehicles.clear();
    admins.clear();
}

std::shared_ptr<Vehicle> FleetManagement::getVehicle(const std::string id) const
{
    for (const auto &vehicle : vehicles)
    {
        if (vehicle->getId() == id)
        {
            return vehicle;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Vehicle>> FleetManagement::getAvailableVehicles()
{
    std::vector<std::shared_ptr<Vehicle>> availableVehicles;
    for (const auto &vehicle : vehicles)
    {
        if (vehicle->getAvailabilityStatus())
        {
            availableVehicles.push_back(vehicle);
        }
    }
    return availableVehicles;
}

std::vector<std::shared_ptr<Vehicle>> FleetManagement::getUnavailableVehicles()
{
    std::vector<std::shared_ptr<Vehicle>> unavailableVehicles;
    for (const auto &vehicle : vehicles)
    {
        if (!vehicle->getAvailabilityStatus())
        {
            unavailableVehicles.push_back(vehicle);
        }
    }
    return unavailableVehicles;
}

std::vector<std::shared_ptr<AdminUser>> FleetManagement::getAdmins() const
{
    return admins;
}

size_t FleetManagement::getVehicleCount() const
{
    return vehicles.size();
}

bool FleetManagement::addVehicle(std::shared_ptr<Vehicle> vehicle)
{
    auto it = std::find_if(vehicles.begin(), vehicles.end(), [&](const std::shared_ptr<Vehicle> &v)
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
    auto it = std::find_if(vehicles.begin(), vehicles.end(), [&](const std::shared_ptr<Vehicle> &vehicle)
                           { return vehicle->getId() == id; });

    if (it != vehicles.end())
    {
        vehicles.erase(it);
        return true;
    }

    return false;
}

bool FleetManagement::addAdmin(std::shared_ptr<AdminUser> admin)
{
    auto it = std::find_if(admins.begin(), admins.end(), [&](const std::shared_ptr<AdminUser> &a)
                           { return a->getId() == admin->getId(); });

    if (it == admins.end())
    {
        admins.push_back(admin);
        return true;
    }

    return false;
}

bool FleetManagement::removeAdmin(const std::string id)
{
    auto it = std::find_if(admins.begin(), admins.end(), [&](const std::shared_ptr<AdminUser> &admin)
                           { return admin->getId() == id; });

    if (it != admins.end())
    {
        admins.erase(it);
        return true;
    }

    return false;
}

std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet)
{
    for (const auto &vehicle : fleet.vehicles)
    {
        os << *vehicle << std::endl;
    }
    return os;
}
