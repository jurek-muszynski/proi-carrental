#pragma once

#include "../vehicle/vehicle.h"
#include <string>
#include <vector>

class FleetManagement
{
public:
    void addVehicle(Vehicle *vehicle);
    void removeVehicle(std::string id);
    Vehicle *getVehicle(std::string id);
    std::vector<Vehicle *> getAvailableVehicles();

private:
    std::vector<Vehicle *> vehicles;
};