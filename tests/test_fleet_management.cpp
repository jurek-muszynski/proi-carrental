#include "gtest/gtest.h"
#include "../src/fleet/fleet_management.h"
#include "../src/rental/rental.h"
#include "../src/rental/rental_management.h"

TEST(FleetManagementTest, Constructor) {
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0));

    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>(vehicles);
    EXPECT_EQ(fleet->getAvailableVehicles().size(), 1);
    EXPECT_EQ(fleet->getAvailableVehicles()[0]->getId(), "1");
}

TEST(FleetManagementTest, AddAndRemoveVehicle)
{
    std::shared_ptr<FleetManagement> fleetManagement = std::make_shared<FleetManagement>();
    auto vehicle1 = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    fleetManagement->addVehicle(vehicle1);

    auto vehicle2 = std::make_shared<Vehicle>("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    fleetManagement->addVehicle(vehicle2);

    EXPECT_EQ(fleetManagement->getVehicle("1")->getMake(), "Toyota");
    EXPECT_EQ(fleetManagement->getVehicle("2")->getMake(), "Honda");

    fleetManagement->removeVehicle("2");
    EXPECT_EQ(fleetManagement->getVehicle("2"), nullptr);
}

TEST(FleetManagementTest, AddAndRemoveVehicle2)
{
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    fleet->addVehicle(vehicle);
    EXPECT_EQ(fleet->getVehicle("1"), vehicle);
    fleet->removeVehicle("1");
    EXPECT_EQ(fleet->getVehicle("1"), nullptr);
}

TEST(FleetManagementTest, GetAvailableVehicles)
{
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();
    auto vehicle1 = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    auto vehicle2 = std::make_shared<Vehicle>("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    fleet->addVehicle(vehicle1);
    fleet->addVehicle(vehicle2);
    std::vector<std::shared_ptr<Vehicle>> availableVehicles = fleet->getAvailableVehicles();
    EXPECT_EQ(availableVehicles.size(), 1);
    EXPECT_EQ(availableVehicles[0], vehicle1);
}

TEST(FleetManagementTest, GetAvailableVehiclesAfterRental)
{
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();
    std::shared_ptr<RentalManagement> rentalManagement = std::make_shared<RentalManagement>();
    auto vehicle1 = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    auto vehicle2 = std::make_shared<Vehicle>("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    auto vehicle3 = std::make_shared<Vehicle>("3", "GHI789", "Ford", "Fiesta", 2019, "Red", "Automatic", "Gasoline", 5, true, 100.0);
    fleet->addVehicle(vehicle1);
    fleet->addVehicle(vehicle2);
    fleet->addVehicle(vehicle3);

    std::vector<std::shared_ptr<Vehicle>> availableVehicles = fleet->getAvailableVehicles();
    EXPECT_EQ(availableVehicles.size(), 2);
    EXPECT_EQ(availableVehicles[0], vehicle1);

    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto rental = std::make_shared<Rental>("1", customer, vehicle1, 7);
    rentalManagement->openRental(rental);

    availableVehicles = fleet->getAvailableVehicles();
    EXPECT_EQ(availableVehicles.size(), 1);
    EXPECT_EQ(availableVehicles[0], vehicle3);
}

TEST(FleetManagementTest, GetUnavailableVehicles) {
    std::shared_ptr<Vehicle> vehicle1 = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    std::shared_ptr<Vehicle> vehicle2 = std::make_shared<Vehicle>("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    std::shared_ptr<Vehicle> vehicle3 = std::make_shared<Vehicle>("3", "GHI789", "Ford", "Fiesta", 2019, "Red", "Automatic", "Gasoline", 5, true, 100.0);

    std::shared_ptr<FleetManagement> fm = std::make_shared<FleetManagement>(std::vector<std::shared_ptr<Vehicle>>{vehicle1, vehicle2, vehicle3});

    std::vector<std::shared_ptr<Vehicle>> unavailableVehicles = fm->getUnavailableVehicles();
    ASSERT_EQ(unavailableVehicles.size(), 1);
}

TEST(FleetManagementTest, AddAdmin) {
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    EXPECT_TRUE(fleet->addAdmin(admin));
    EXPECT_EQ(fleet->getAdmins().size(), 1);
    EXPECT_EQ(fleet->getAdmins()[0]->getId(), "1");
}

TEST(FleetManagementTest, RemoveAdmin) {
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    fleet->addAdmin(admin);

    EXPECT_TRUE(fleet->removeAdmin("1"));
    EXPECT_EQ(fleet->getAdmins().size(), 0);
}

TEST(FleetManagementTest, AddAndRemoveAdmin) {
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "PostalCode");
    std::shared_ptr<AdminUser> admin = std::make_shared<AdminUser>("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", address);

    EXPECT_TRUE(fleet->addAdmin(admin));
    EXPECT_EQ(fleet->getAdmins().size(), 1);
    EXPECT_EQ(fleet->getAdmins()[0]->getId(), "1");

    EXPECT_TRUE(fleet->removeAdmin("1"));
    EXPECT_EQ(fleet->getAdmins().size(), 0);
}

TEST(FleetManagementTest, AddAdminIsNull) {
    std::shared_ptr<AdminUser> admin = nullptr;

    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();

    EXPECT_FALSE(fleet->addAdmin(admin));
}

TEST(FleetManagementTest, RemoveAdminNonExistent) {
    std::shared_ptr<FleetManagement> fleet = std::make_shared<FleetManagement>();

    EXPECT_FALSE(fleet->removeAdmin("1"));
}