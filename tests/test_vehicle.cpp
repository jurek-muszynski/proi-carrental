#include <gtest/gtest.h>
#include "../src/vehicle/vehicle.h"

TEST(VehicleTest, GettersAndSetters)
{
    Vehicle vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    vehicle.setMake("Honda");
    vehicle.setModel("Civic");
    vehicle.setYear(2021);
    vehicle.setColor("Black");
    vehicle.setTransmissionType("Manual");
    vehicle.setFuelType("Diesel");
    vehicle.setSeatingCapacity(4);
    vehicle.setAvailabilityStatus(false);
    vehicle.setRentalRates(120.0);

    EXPECT_EQ(vehicle.getMake(), "Honda");
    EXPECT_EQ(vehicle.getModel(), "Civic");
    EXPECT_EQ(vehicle.getYear(), 2021);
    EXPECT_EQ(vehicle.getColor(), "Black");
    EXPECT_EQ(vehicle.getTransmissionType(), "Manual");
    EXPECT_EQ(vehicle.getFuelType(), "Diesel");
    EXPECT_EQ(vehicle.getSeatingCapacity(), 4);
    EXPECT_EQ(vehicle.getAvailabilityStatus(), false);
    EXPECT_EQ(vehicle.getRentalRates(), 120.0);
}

TEST(VehicleTest, ConstructorAndGetters)
{
    Address address("1", "123 Main St", "Springfield", "USA", "12345");
    Location location(101, "Main Office", &address);
    Vehicle vehicle("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0);
    vehicle.updateLocation(&location);

    EXPECT_EQ(vehicle.getId(), "V1");
    EXPECT_EQ(vehicle.getLicensePlate(), "XYZ123");
    EXPECT_EQ(vehicle.getMake(), "Toyota");
    EXPECT_EQ(vehicle.getModel(), "Camry");
    EXPECT_EQ(vehicle.getYear(), 2020);
    EXPECT_EQ(vehicle.getColor(), "Red");
    EXPECT_EQ(vehicle.getTransmissionType(), "Automatic");
    EXPECT_EQ(vehicle.getFuelType(), "Gasoline");
    EXPECT_EQ(vehicle.getSeatingCapacity(), 5);
    EXPECT_EQ(vehicle.getAvailabilityStatus(), true);
    EXPECT_EQ(vehicle.getRentalRates(), 50.0);
    EXPECT_EQ(vehicle.getLocation(), &location);
}

TEST(VehicleTest, InitialLocation)
{
    Vehicle vehicle("V2", "ABC456", "Honda", "Civic", 2019, "Blue", "Manual", "Diesel", 4, false, 40.0);

    EXPECT_EQ(vehicle.getLocation(), nullptr);
}

TEST(VehicleTest, UpdateLocation)
{
    Address address1("2", "456 Elm St", "Shelbyville", "USA", "67890");
    Location location1(102, "Branch Office", &address1);
    Vehicle vehicle("V3", "LMN789", "Ford", "Focus", 2018, "Green", "Automatic", "Electric", 5, true, 60.0);
    vehicle.updateLocation(&location1);

    EXPECT_EQ(vehicle.getLocation(), &location1);

    Address address2("3", "789 Oak St", "Capital City", "USA", "10101");
    Location location2(103, "Warehouse", &address2);
    vehicle.updateLocation(&location2);

    EXPECT_EQ(vehicle.getLocation(), &location2);
    EXPECT_EQ(vehicle.getLocation()->getName(), "Warehouse");
    EXPECT_EQ(vehicle.getLocation()->getAddress()->getStreet(), "789 Oak St");
}

TEST(VehicleAvailabilityTest, InitialAvailabilityStatus)
{
    Address address("1", "123 Main St", "Springfield", "USA", "12345");
    Location location(101, "Main Office", &address);
    Vehicle vehicle("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0);
    vehicle.updateLocation(&location);

    EXPECT_TRUE(vehicle.getAvailabilityStatus());

    Vehicle vehicle2("V2", "ABC456", "Honda", "Civic", 2019, "Blue", "Manual", "Diesel", 4, false, 40.0);
    vehicle.updateLocation(&location);

    EXPECT_FALSE(vehicle2.getAvailabilityStatus());
}

TEST(VehicleAvailabilityTest, UpdateAvailabilityStatus)
{
    Address address("2", "456 Elm St", "Shelbyville", "USA", "67890");
    Location location(102, "Branch Office", &address);
    Vehicle vehicle("V3", "LMN789", "Ford", "Focus", 2018, "Green", "Automatic", "Electric", 5, true, 60.0);
    vehicle.updateLocation(&location);

    EXPECT_TRUE(vehicle.getAvailabilityStatus());

    vehicle.updateAvailabilityStatus(false);
    EXPECT_FALSE(vehicle.getAvailabilityStatus());

    vehicle.updateAvailabilityStatus(true);
    EXPECT_TRUE(vehicle.getAvailabilityStatus());
}

TEST(VehicleAvailabilityTest, AvailabilityAfterRental)
{
    Address address("3", "789 Oak St", "Capital City", "USA", "10101");
    Location location(103, "Warehouse", &address);
    Vehicle vehicle("V4", "PQR123", "Tesla", "Model 3", 2021, "White", "Automatic", "Electric", 5, true, 100.0);
    vehicle.updateLocation(&location);

    // Simulate renting the vehicle
    vehicle.updateAvailabilityStatus(false);
    EXPECT_FALSE(vehicle.getAvailabilityStatus());

    // Simulate returning the vehicle
    vehicle.updateAvailabilityStatus(true);
    EXPECT_TRUE(vehicle.getAvailabilityStatus());
}

TEST(VehicleAvailabilityTest, AvailabilityDuringMaintenance)
{
    Address address("4", "321 Pine St", "Metropolis", "USA", "20202");
    Location location(104, "Depot", &address);
    Vehicle vehicle("V5", "XYZ789", "Chevrolet", "Malibu", 2021, "Black", "Automatic", "Hybrid", 5, true, 55.0);
    vehicle.updateLocation(&location);

    // Simulate sending the vehicle for maintenance
    vehicle.updateAvailabilityStatus(false);
    EXPECT_FALSE(vehicle.getAvailabilityStatus());

    // Simulate vehicle being ready for rental again
    vehicle.updateAvailabilityStatus(true);
    EXPECT_TRUE(vehicle.getAvailabilityStatus());
}