#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../admin/admin.h"
#include "../vehicle/vehicle.h"

class FleetManagement
{
private:
    std::vector<Vehicle *> vehicles;
    std::vector<AdminUser *> admins;

public:
    FleetManagement(std::vector<Vehicle *> vehicles = {});
    ~FleetManagement();

    Vehicle *getVehicle(const std::string id) const;
    std::vector<Vehicle *> getAvailableVehicles();
    std::vector<Vehicle *> getUnavailableVehicles();
    std::vector<AdminUser*> getAdmins() const;

    size_t getVehicleCount() const;

    bool addVehicle(Vehicle *vehicle);
    bool removeVehicle(const std::string id);
    bool addAdmin(AdminUser *admin);
    bool removeAdmin(const std::string id);

    friend std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet);
};
