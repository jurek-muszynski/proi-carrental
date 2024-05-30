#include "gtest/gtest.h"
#include "../src/fleet/fleet_management.h"

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
