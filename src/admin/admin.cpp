#include "admin.h"

AdminUser::AdminUser(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, std::shared_ptr<Address> address)
    : User(id, firstName, lastName, birthDate, gender, email, phoneNumber, address)
{
}

void AdminUser::performVehicleMaintenance(std::shared_ptr<Vehicle> vehicle)
{
    vehicle->updateAvailabilityStatus(false);
}

void AdminUser::finishVehicleMaintenance(std::shared_ptr<Vehicle> vehicle)
{
    vehicle->updateAvailabilityStatus(true);
}

std::ostream &operator<<(std::ostream &os, const AdminUser &adminUser)
{
    os << adminUser.getFirstName() << " " << adminUser.getLastName();
    os << " ID: " << adminUser.getId();

    return os;
}
