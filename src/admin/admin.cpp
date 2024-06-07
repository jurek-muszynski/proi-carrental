#include "admin.h"

AdminUser::AdminUser(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, Address *address)
    : User(id, firstName, lastName, birthDate, gender, email, phoneNumber, address)
{
}

void AdminUser::performVehicleMaintenance(Vehicle *vehicle)
{
    vehicle->updateAvailabilityStatus(false);
}

void AdminUser::finishVehicleMaintenance(Vehicle *vehicle)
{
    vehicle->updateAvailabilityStatus(true);
}

std::ostream &operator<<(std::ostream &os, const AdminUser &adminUser)
{
    os << adminUser.getFirstName() << " " << adminUser.getLastName();
    os << " ID: " << adminUser.getId();

    return os;
}
