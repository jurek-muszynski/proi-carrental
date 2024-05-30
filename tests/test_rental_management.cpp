#include "gtest/gtest.h"
#include "../src/rental/rental_management.h"

TEST(RentalManagementTest, CreateAndCloseRental)
{
    RentalManagement rentalManagement;
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer1 = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental *rental1 = new Rental("1", customer1, vehicle1, 7);
    rentalManagement.openRental(rental1);

    birthDate.tm_year = 1991 - 1900;
    birthDate.tm_mon = 2 - 1;
    birthDate.tm_mday = 2;
    Address *address2 = new Address("id2", "321 Avenue", "Town", "Province", "54321");
    Customer *customer2 = new Customer("2", "Jane", "Doe", birthDate, "Female", "jane.doe@example.com", "0987654321", address2);
    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, false, 120.0);
    Rental *rental2 = new Rental("2", customer2, vehicle2, 7);
    rentalManagement.openRental(rental2);

    EXPECT_NE(rentalManagement.getRental("1"), nullptr);
    EXPECT_NE(rentalManagement.getRental("2"), nullptr);
    EXPECT_EQ(rentalManagement.getRental("3"), nullptr);
    EXPECT_EQ(rentalManagement.getRental("1")->getCustomer()->getFirstName(), "John");
    EXPECT_EQ(rentalManagement.getRental("2")->getCustomer()->getFirstName(), "Jane");

    rentalManagement.closeRental("2");
    EXPECT_EQ(rentalManagement.getRental("2"), nullptr);
    EXPECT_EQ(rental2->getCustomer(), nullptr);
    EXPECT_EQ(rental2->getVehicle(), nullptr);
    // EXPECT_EQ(rental2, nullptr) TODO: Fix this
}