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
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    std::vector<std::shared_ptr<AdminUser>> admins;

public:
    FleetManagement(std::vector<std::shared_ptr<Vehicle>> vehicles = {});
    ~FleetManagement();

    std::shared_ptr<Vehicle> getVehicle(const std::string id) const;
    std::vector<std::shared_ptr<Vehicle>> getAvailableVehicles();
    std::vector<std::shared_ptr<Vehicle>> getUnavailableVehicles();
    std::vector<std::shared_ptr<AdminUser>> getAdmins() const;

    size_t getVehicleCount() const;

    bool addVehicle(std::shared_ptr<Vehicle> vehicle);
    bool removeVehicle(const std::string id);
    bool addAdmin(std::shared_ptr<AdminUser> admin);
    bool removeAdmin(const std::string id);

    friend std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet);
};
