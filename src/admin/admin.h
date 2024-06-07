#pragma once

#include "../user/user.h"
#include "../vehicle/vehicle.h"

class AdminUser : public User
{
public:
    AdminUser(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, std::shared_ptr<Address> address);
    void performVehicleMaintenance(std::shared_ptr<Vehicle> vehicle);
    void finishVehicleMaintenance(std::shared_ptr<Vehicle> vehicle);

    friend std::ostream &operator<<(std::ostream &os, const AdminUser &adminUser);
};