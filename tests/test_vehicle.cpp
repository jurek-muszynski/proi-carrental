#include <gtest/gtest.h>
#include "../src/vehicle/vehicle.h"

TEST(VehicleTest, ConstructorAndGetters)
{
    Address address("1", "123 Main St", "Springfield", "USA", "12345");
    std::shared_ptr<Location> location = std::make_unique<Location>(101, "Main Office", std::make_unique<Address>(address));
    std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0);
    std::unique_ptr<Vehicle> vehicle2 = std::make_unique<Vehicle>("V2", "ABC456", "Honda", "Civic", 2019, "Blue", "Manual", "Diesel", 4, false, 40.0, location);
    vehicle->updateLocation(location);
    EXPECT_EQ(vehicle->getId(), "V1");
    EXPECT_EQ(vehicle->getLicensePlate(), "XYZ123");
    EXPECT_EQ(vehicle->getMake(), "Toyota");
    EXPECT_EQ(vehicle->getModel(), "Camry");
    EXPECT_EQ(vehicle->getYear(), 2020);
    EXPECT_EQ(vehicle->getColor(), "Red");
    EXPECT_EQ(vehicle->getTransmissionType(), "Automatic");
    EXPECT_EQ(vehicle->getFuelType(), "Gasoline");
    EXPECT_EQ(vehicle->getSeatingCapacity(), 5);
    EXPECT_EQ(vehicle->getAvailabilityStatus(), true);
    EXPECT_EQ(vehicle->getRentalRates(), 50.0);
    EXPECT_EQ(vehicle->getLocation()->getLocationId(), location->getLocationId());

    EXPECT_EQ(vehicle2->getId(), "V2");
    EXPECT_EQ(vehicle2->getLicensePlate(), "ABC456");
    EXPECT_EQ(vehicle2->getMake(), "Honda");
    EXPECT_EQ(vehicle2->getModel(), "Civic");
    EXPECT_EQ(vehicle2->getYear(), 2019);
    EXPECT_EQ(vehicle2->getColor(), "Blue");
    EXPECT_EQ(vehicle2->getTransmissionType(), "Manual");
    EXPECT_EQ(vehicle2->getFuelType(), "Diesel");
    EXPECT_EQ(vehicle2->getSeatingCapacity(), 4);
    EXPECT_EQ(vehicle2->getAvailabilityStatus(), false);
    EXPECT_EQ(vehicle2->getRentalRates(), 40.0);
    EXPECT_EQ(vehicle2->getLocation()->getLocationId(), location->getLocationId());
}

TEST(VehicleTest, InitialLocation)
{
    std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>("V2", "ABC456", "Honda", "Civic", 2019, "Blue", "Manual", "Diesel", 4, false, 40.0);

    EXPECT_EQ(vehicle->getLocation(), nullptr);
}

TEST(VehicleTest, UpdateLocation)
{
    Address address1("2", "456 Elm St", "Shelbyville", "USA", "67890");
    std::shared_ptr<Location> location1 = std::make_shared<Location>(102, "Branch Office", std::make_unique<Address>(address1));
    std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>("V3", "LMN789", "Ford", "Focus", 2018, "Green", "Automatic", "Electric", 5, true, 60.0);
    vehicle->updateLocation(location1);

    EXPECT_EQ(vehicle->getLocation(), location1);

    Address address2("3", "789 Oak St", "Capital City", "USA", "10101");
    std::shared_ptr<Location> location2 = std::make_shared<Location>(103, "Warehouse", std::make_unique<Address>(address2));
    vehicle->updateLocation(location2);

    EXPECT_EQ(vehicle->getLocation(), location2);
    EXPECT_EQ(vehicle->getLocation()->getName(), "Warehouse");
    EXPECT_EQ(vehicle->getLocation()->getAddress()->getStreet(), "789 Oak St");
}
TEST(VehicleTest, InitialAvailabilityStatus)
{
    auto address = std::make_shared<Address>("1", "123 Main St", "Springfield", "USA", "12345");
    auto location = std::make_shared<Location>(101, "Main Office", address);
    auto vehicle = std::make_shared<Vehicle>("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0, location);

    EXPECT_TRUE(vehicle->getAvailabilityStatus());

    auto vehicle2 = std::make_shared<Vehicle>("V2", "ABC456", "Honda", "Civic", 2019, "Blue", "Manual", "Diesel", 4, false, 40.0, location);

    EXPECT_FALSE(vehicle2->getAvailabilityStatus());
}

TEST(VehicleTest, UpdateAvailabilityStatus)
{
    auto address = std::make_shared<Address>("2", "456 Elm St", "Shelbyville", "USA", "67890");
    auto location = std::make_shared<Location>(102, "Branch Office", address);
    auto vehicle = std::make_shared<Vehicle>("V3", "LMN789", "Ford", "Focus", 2018, "Green", "Automatic", "Electric", 5, true, 60.0, location);

    EXPECT_TRUE(vehicle->getAvailabilityStatus());

    vehicle->updateAvailabilityStatus(false);
    EXPECT_FALSE(vehicle->getAvailabilityStatus());

    vehicle->updateAvailabilityStatus(true);
    EXPECT_TRUE(vehicle->getAvailabilityStatus());
}

TEST(VehicleTest, AvailabilityAfterRental)
{
    auto address = std::make_shared<Address>("3", "789 Oak St", "Capital City", "USA", "10101");
    auto location = std::make_shared<Location>(103, "Warehouse", address);
    auto vehicle = std::make_shared<Vehicle>("V4", "PQR123", "Tesla", "Model 3", 2021, "White", "Automatic", "Electric", 5, true, 100.0, location);

    // Simulate renting the vehicle
    vehicle->updateAvailabilityStatus(false);
    EXPECT_FALSE(vehicle->getAvailabilityStatus());

    // Simulate returning the vehicle
    vehicle->updateAvailabilityStatus(true);
    EXPECT_TRUE(vehicle->getAvailabilityStatus());
}

TEST(VehicleTest, AvailabilityDuringMaintenance)
{
    auto address = std::make_shared<Address>("4", "321 Pine St", "Metropolis", "USA", "20202");
    auto location = std::make_shared<Location>(104, "Depot", address);
    auto vehicle = std::make_shared<Vehicle>("V5", "XYZ789", "Chevrolet", "Malibu", 2021, "Black", "Automatic", "Hybrid", 5, true, 55.0, location);

    // Simulate sending the vehicle for maintenance
    vehicle->updateAvailabilityStatus(false);
    EXPECT_FALSE(vehicle->getAvailabilityStatus());

    // Simulate vehicle being ready for rental again
    vehicle->updateAvailabilityStatus(true);
    EXPECT_TRUE(vehicle->getAvailabilityStatus());
}

TEST(VehicleTest, DestructorCalled)
{
    auto address = std::make_shared<Address>("1", "123 Main St", "Springfield", "USA", "12345");
    auto location = std::make_shared<Location>(101, "Main Office", address);

    auto vehicle = std::make_shared<Vehicle>("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0, location);

    EXPECT_EQ(vehicle->getLocation(), location);
    vehicle.reset();
    EXPECT_EQ(vehicle, nullptr);
}

TEST(VehicleTest, MultipleVehiclesSameLocation)
{
    auto address = std::make_shared<Address>("1", "123 Main St", "Springfield", "USA", "12345");
    auto location = std::make_shared<Location>(101, "Main Office", address);

    auto vehicle1 = std::make_shared<Vehicle>("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0, location);
    auto vehicle2 = std::make_shared<Vehicle>("V2", "ABC456", "Honda", "Civic", 2019, "Blue", "Manual", "Diesel", 4, false, 40.0, location);

    vehicle1.reset();
    vehicle2.reset();
    EXPECT_EQ(vehicle1, nullptr);
    EXPECT_EQ(vehicle2, nullptr);
}