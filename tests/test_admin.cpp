#include "gtest/gtest.h"
#include "../src/admin/admin.h"

TEST(AdminUserTest, Constructor)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1980 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    EXPECT_EQ(admin->getId(), "1");
    EXPECT_EQ(admin->getFirstName(), "Admin");
    EXPECT_EQ(admin->getLastName(), "User");
    EXPECT_EQ(admin->getGender(), "M");
    EXPECT_EQ(admin->getEmail(), "admin.user@example.com");
    EXPECT_EQ(admin->getPhoneNumber(), "1234567890");
    EXPECT_EQ(admin->getAddress(), address);
}

TEST(AdminUserTest, PerformAndFinishVehicleMaintenance)
{
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    std::shared_ptr<Vehicle> vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);

    admin->performVehicleMaintenance(vehicle);
    EXPECT_FALSE(vehicle->getAvailabilityStatus());

    admin->finishVehicleMaintenance(vehicle);
    EXPECT_TRUE(vehicle->getAvailabilityStatus());
}

TEST(AdminUserTest, PerformVehicleMaintenanceOnUnavailableVehicle)
{
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    std::shared_ptr<Vehicle> vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, false, 100.0);

    admin->performVehicleMaintenance(vehicle);
    EXPECT_FALSE(vehicle->getAvailabilityStatus());
}

TEST(AdminUserTest, FinishVehicleMaintenanceOnAvailableVehicle)
{
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    std::shared_ptr<Vehicle> vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);

    admin->finishVehicleMaintenance(vehicle);
    EXPECT_TRUE(vehicle->getAvailabilityStatus());
}

TEST(AdminUserTest, Print)
{
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    std::ostringstream os;
    os << *admin;
    EXPECT_EQ(os.str(), "Admin User ID: 1");
}