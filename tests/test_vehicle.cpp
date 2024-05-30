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