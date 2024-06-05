#pragma once

#include "../user/user.h"
#include "../vehicle/vehicle.h"

class AdminUser : public User
{
public:
    AdminUser(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, Address *address);

    void performVehicleMaintenance(Vehicle *vehicle);
    void finishVehicleMaintenance(Vehicle *vehicle);

    // overload the << operator that is derived from the user class
    friend std::ostream &operator<<(std::ostream &os, const AdminUser &adminUser);
};