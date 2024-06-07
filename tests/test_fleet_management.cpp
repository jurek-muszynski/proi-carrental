#include "gtest/gtest.h"
#include "../src/fleet/fleet_management.h"
#include "../src/rental/rental.h"
#include "../src/rental/rental_management.h"

TEST(FleetManagementTest, Constructor) {
    std::vector<Vehicle *> vehicles;
    vehicles.push_back(new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0));

    FleetManagement *fleet = new FleetManagement(vehicles);
    EXPECT_EQ(fleet->getAvailableVehicles().size(), 1);
    EXPECT_EQ(fleet->getAvailableVehicles()[0]->getId(), "1");
}

TEST(FleetManagementTest, AddAndRemoveVehicle)
{
    FleetManagement fleetManagement;
    Vehicle *vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    fleetManagement.addVehicle(vehicle1);

    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    fleetManagement.addVehicle(vehicle2);

    EXPECT_EQ(fleetManagement.getVehicle("1")->getMake(), "Toyota");
    EXPECT_EQ(fleetManagement.getVehicle("2")->getMake(), "Honda");

    fleetManagement.removeVehicle("2");
    EXPECT_EQ(fleetManagement.getVehicle("2"), nullptr);
}

TEST(FleetManagementTest, AddAndRemoveVehicle2)
{
    FleetManagement fleet;
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    fleet.addVehicle(vehicle);
    EXPECT_EQ(fleet.getVehicle("1"), vehicle);
    fleet.removeVehicle("1");
    EXPECT_EQ(fleet.getVehicle("1"), nullptr);
}

TEST(FleetManagementTest, GetAvailableVehicles)
{
    FleetManagement fleet;
    Vehicle *vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    fleet.addVehicle(vehicle1);
    fleet.addVehicle(vehicle2);
    std::vector<Vehicle *> availableVehicles = fleet.getAvailableVehicles();
    EXPECT_EQ(availableVehicles.size(), 1);
    EXPECT_EQ(availableVehicles[0], vehicle1);
}

TEST(FleetManagementTest, GetAvailableVehiclesAfterRental)
{
    FleetManagement fleet;
    RentalManagement rentalManagement;
    Vehicle *vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    Vehicle *vehicle3 = new Vehicle("3", "GHI789", "Ford", "Fiesta", 2019, "Red", "Automatic", "Gasoline", 5, true, 100.0);
    fleet.addVehicle(vehicle1);
    fleet.addVehicle(vehicle2);
    fleet.addVehicle(vehicle3);

    std::vector<Vehicle *> availableVehicles = fleet.getAvailableVehicles();
    EXPECT_EQ(availableVehicles.size(), 2);
    EXPECT_EQ(availableVehicles[0], vehicle1);

    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Rental *rental = new Rental("1", customer, vehicle1, 7);

    availableVehicles = fleet.getAvailableVehicles();
    EXPECT_EQ(availableVehicles.size(), 1);
    EXPECT_EQ(availableVehicles[0], vehicle3);
}

TEST(FleetManagementTest, GetUnavailableVehicles) {
    Vehicle *vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    Vehicle *vehicle3 = new Vehicle("3", "GHI789", "Ford", "Fiesta", 2019, "Red", "Automatic", "Gasoline", 5, true, 100.0);

    FleetManagement fm({vehicle1, vehicle2, vehicle3});

    std::vector<Vehicle*> unavailableVehicles = fm.getUnavailableVehicles();
    ASSERT_EQ(unavailableVehicles.size(), 1);
    EXPECT_EQ(unavailableVehicles[0], vehicle2);
}

TEST(FleetManagementTest, AddAdmin) {
    FleetManagement fleet;
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    Address address("Street", "City", "State", "Country", "PostalCode");
    AdminUser *admin = new AdminUser("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", &address);

    EXPECT_TRUE(fleet.addAdmin(admin));
    EXPECT_EQ(fleet.getAdmins().size(), 1);
    EXPECT_EQ(fleet.getAdmins()[0]->getId(), "1");
}

TEST(FleetManagementTest, RemoveAdmin) {
    FleetManagement fleet;
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    Address address("Street", "City", "State", "Country", "PostalCode");
    AdminUser *admin = new AdminUser("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", &address);

    fleet.addAdmin(admin);

    EXPECT_TRUE(fleet.removeAdmin("1"));
    EXPECT_EQ(fleet.getAdmins().size(), 0);
}

TEST(FleetManagementTest, AddAndRemoveAdmin) {
    FleetManagement fleet;
    std::tm birthDate = {};
    birthDate.tm_year = 2000 - 1900;
    birthDate.tm_mon = 1;
    birthDate.tm_mday = 1;
    Address address("Street", "City", "State", "Country", "PostalCode");
    AdminUser *admin = new AdminUser("1", "Admin", "User", birthDate, "M", "admin.user@example.com", "1234567890", &address);

    EXPECT_TRUE(fleet.addAdmin(admin));
    EXPECT_EQ(fleet.getAdmins().size(), 1);
    EXPECT_EQ(fleet.getAdmins()[0]->getId(), "1");

    EXPECT_TRUE(fleet.removeAdmin("1"));
    EXPECT_EQ(fleet.getAdmins().size(), 0);
}

TEST(FleetManagementTest, AddAdminIsNull) {
    AdminUser *admin = nullptr;

    FleetManagement fleet;

    EXPECT_FALSE(fleet.addAdmin(admin));
}

TEST(FleetManagementTest, RemoveAdminNonExistent) {
    FleetManagement fleet;

    EXPECT_FALSE(fleet.removeAdmin("1"));
}