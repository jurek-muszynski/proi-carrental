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
    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, true, 120.0);
    Rental *rental2 = new Rental("2", customer2, vehicle2, 7);
    rentalManagement.openRental(rental2);

    EXPECT_NE(rentalManagement.getRental("1"), nullptr);
    EXPECT_NE(rentalManagement.getRental("2"), nullptr);
    EXPECT_EQ(rentalManagement.getRental("3"), nullptr);
    EXPECT_EQ(rentalManagement.getRental("1")->getCustomer()->getFirstName(), "John");
    EXPECT_EQ(rentalManagement.getRental("2")->getCustomer()->getFirstName(), "Jane");

    rentalManagement.closeRental("2");
    EXPECT_EQ(rentalManagement.getRental("2"), nullptr);
    delete rental2;
    EXPECT_EQ(rental2->getCustomer(), nullptr);
    EXPECT_EQ(rental2->getVehicle(), nullptr);
    // EXPECT_EQ(rental2, nullptr) TODO: Fix this
}

TEST(RentalManagementTest, RentUnavailableVehicle)
{
    RentalManagement rentalManagement;

    // Create a customer
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900; // years since 1900
    birthDate.tm_mon = 1 - 1;        // months since January (0-11)
    birthDate.tm_mday = 1;           // day of the month (1-31)
    Customer customer("C004", "Bob", "Smith", birthDate, "Male", "bob@example.com", "444555666", nullptr);

    // Create an unavailable vehicle
    Location location(1, "Main Office", nullptr);
    Vehicle vehicle("V004", "GHI789", "Chevrolet", "Malibu", 2021, "White", "Automatic", "Petrol", 5, false, 70.0);
    vehicle.updateLocation(&location);

    // Attempt to open a rental for the unavailable vehicle
    EXPECT_THROW(rentalManagement.openRental(new Rental("R004", &customer, &vehicle, 2)), std::invalid_argument);

    // Check if the rental was not added to the rental management system
    EXPECT_EQ(rentalManagement.getRental("R004"), nullptr);
}

// Test for renting a vehicle and returning it to a different location
TEST(RentalManagementTest, RentAndReturnToDifferentLocation)
{
    RentalManagement rentalManagement;

    // Create a customer
    std::tm birthDate = {};
    birthDate.tm_year = 1985 - 1900; // years since 1900
    birthDate.tm_mon = 3 - 1;        // months since January (0-11)
    birthDate.tm_mday = 15;          // day of the month (1-31)
    Customer customer("C005", "Emily", "Johnson", birthDate, "Female", "emily@example.com", "777888999", nullptr);
    Address *address1 = new Address("id1", "123 Street", "City", "State", "12345");
    Address *address2 = new Address("id2", "123 Street", "City", "State", "12345");

    // Create a vehicle
    Location pickupLocation(1, "Pickup Location", address1);
    Vehicle vehicle("V005", "JKL123", "Ford", "Escape", 2020, "Silver", "Automatic", "Petrol", 5, true, 60.0);
    vehicle.updateLocation(&pickupLocation);

    // Open a rental
    Rental rental("R005", &customer, &vehicle, 4);
    rentalManagement.openRental(&rental);

    // Simulate returning the vehicle to a different location
    Location dropoffLocation(3, "Dropoff Location", address2);
    vehicle.updateLocation(&dropoffLocation);

    // Close the rental
    rentalManagement.closeRental("R005");

    // Check if the rental was successfully closed
    EXPECT_EQ(rentalManagement.getRental("R005"), nullptr);
}

TEST(RentalManagementTest, CustomerTriesToRentSecondVehicle)
{
    RentalManagement rentalManagement;

    std::tm birthDate = {};
    birthDate.tm_year = 1985 - 1900; // years since 1900
    birthDate.tm_mon = 3 - 1;        // months since January (0-11)
    birthDate.tm_mday = 15;          // day of the month (1-31)
    Customer customer("C005", "Emily", "Johnson", birthDate, "Female", "emily@example.com", "777888999", nullptr);
    Address *address1 = new Address("id1", "123 Street", "City", "State", "12345");
    Address *address2 = new Address("id2", "123 Street", "City", "State", "12345");

    Location pickupLocation(1, "Pickup Location", address1);
    Vehicle vehicle("V005", "JKL123", "Ford", "Escape", 2020, "Silver", "Automatic", "Petrol", 5, true, 60.0);
    Vehicle vehicle2("V006", "JKL124", "Ford", "Escape", 2020, "Silver", "Automatic", "Petrol", 5, true, 60.0);
    vehicle.updateLocation(&pickupLocation);
    vehicle2.updateLocation(&pickupLocation);

    Rental rental1("R005", &customer, &vehicle, 4);
    Rental rental2("R006", &customer, &vehicle2, 4);
    EXPECT_TRUE(rentalManagement.openRental(&rental1));
    EXPECT_FALSE(rentalManagement.openRental(&rental2));
}

TEST(RentalManagementTest, CurrentCustomers)
{
    RentalManagement rentalManagement;

    std::tm birthDate = {};
    birthDate.tm_year = 1985 - 1900; // years since 1900
    birthDate.tm_mon = 3 - 1;        // months since January (0-11)
    birthDate.tm_mday = 15;          // day of the month (1-31)

    Customer customer1("C005", "Emily", "Johnson", birthDate, "Female", "emily@example.com", "777888999", nullptr);
    Customer customer2("C006", "John", "Doe", birthDate, "Male", "", "", nullptr);
    std::vector<Customer *> customers = {&customer1, &customer2};

    Address *address1 = new Address("id1", "123 Street", "City", "State", "12345");
    Address *address2 = new Address("id2", "123 Street", "City", "State", "12345");
    Location pickupLocation(1, "Pickup Location", address1);
    Vehicle vehicle("V005", "JKL123", "Ford", "Escape", 2020, "Silver", "Automatic", "Petrol", 5, true, 60.0, &pickupLocation);
    Vehicle vehicle2("V006", "JKL124", "Ford", "Escape", 2020, "Silver", "Automatic", "Petrol", 5, true, 60.0, &pickupLocation);

    Rental rental1("R005", &customer1, &vehicle, 4);
    Rental rental2("R006", &customer2, &vehicle2, 4);

    EXPECT_TRUE(rentalManagement.openRental(&rental1));
    EXPECT_TRUE(rentalManagement.openRental(&rental2));

    EXPECT_EQ(rentalManagement.getCurrentCustomers().size(), 2);
    EXPECT_EQ(rentalManagement.getCurrentCustomers(), customers);
}

TEST(RentalManagementTest, RentalsToBeTerminated)
{
    RentalManagement rentalManagement;

    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;

    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer1 = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Customer *customer2 = new Customer("C006", "John", "Doe", birthDate, "Male", "", "", nullptr);
    Vehicle *vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Vehicle *vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, true, 120.0);
    Rental *rental1 = new Rental("1", customer1, vehicle1, 2, std::chrono::system_clock::now());
    Rental *rental2 = new Rental("2", customer2, vehicle2, 3, std::chrono::system_clock::now());

    rentalManagement.openRental(rental1);
    rentalManagement.openRental(rental2);

    std::chrono::system_clock::time_point time_after_an_hour = std::chrono::system_clock::now() + std::chrono::hours(1);
    std::chrono::system_clock::time_point time_after_two_hours = std::chrono::system_clock::now() + std::chrono::hours(2);
    std::chrono::system_clock::time_point time_after_three_hours = std::chrono::system_clock::now() + std::chrono::hours(3);

    auto rentalsToBeTerminated = rentalManagement.getRentalsToBeTerminated(time_after_an_hour);
    EXPECT_EQ(rentalsToBeTerminated.size(), 0);

    rentalsToBeTerminated = rentalManagement.getRentalsToBeTerminated(time_after_two_hours);
    EXPECT_EQ(rentalsToBeTerminated.size(), 1);
    EXPECT_EQ(rentalsToBeTerminated[0]->getId(), "1");

    rentalsToBeTerminated = rentalManagement.getRentalsToBeTerminated(time_after_three_hours);
    EXPECT_EQ(rentalsToBeTerminated.size(), 2);
    EXPECT_EQ(rentalsToBeTerminated[0]->getId(), "1");
    EXPECT_EQ(rentalsToBeTerminated[1]->getId(), "2");
}