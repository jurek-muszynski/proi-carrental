#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../vehicle/vehicle.h"

class FleetManagement
{
private:
    std::vector<Vehicle *> vehicles;

public:
    FleetManagement(std::vector<Vehicle *> vehicles = {});
    ~FleetManagement();

    Vehicle *getVehicle(const std::string id) const;
    std::vector<Vehicle *> getAvailableVehicles();

    bool addVehicle(Vehicle *vehicle);
    bool removeVehicle(const std::string id);

    friend std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet);
};
