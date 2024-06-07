#include "gtest/gtest.h"
#include "../src/rental/rental_management.h"

class RentalManagementTest : public ::testing::Test {
protected:
    RentalManagement rentalManagement;
    Address* address1;
    Address* address2;
    Customer* customer1;
    Customer* customer2;
    Vehicle* vehicle1;
    Vehicle* vehicle2;
    Rental* rental1;
    Rental* rental2;

    void SetUp() override {
        std::tm birthDate = {};
        birthDate.tm_year = 1990 - 1900;
        birthDate.tm_mon = 1 - 1;
        birthDate.tm_mday = 1;
        
        address1 = new Address("id1", "123 Street", "City", "State", "12345");
        customer1 = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address1);

        address2 = new Address("id2", "456 Avenue", "Town", "Province", "67890");
        customer2 = new Customer("2", "Jane", "Doe", birthDate, "Female", "jane.doe@example.com", "0987654321", address2);

        vehicle1 = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
        vehicle2 = new Vehicle("2", "DEF456", "Honda", "Civic", 2021, "Black", "Manual", "Diesel", 4, true, 120.0);

        rental1 = new Rental("1", customer1, vehicle1, 7);
        rental2 = new Rental("2", customer2, vehicle2, 10);

        rentalManagement.openRental(rental1);
    }

    void TearDown() override {
        delete customer1;
        delete customer2;
        delete vehicle1;
        delete vehicle2;
        delete rental1;
        delete rental2;
    }
};

TEST_F(RentalManagementTest, IsCustomerCurrentlyRenting_True) {
    EXPECT_TRUE(rentalManagement.isCustomerCurrentlyRenting(customer1));
}

TEST_F(RentalManagementTest, IsCustomerCurrentlyRenting_False) {
    EXPECT_FALSE(rentalManagement.isCustomerCurrentlyRenting(customer2));
}

TEST_F(RentalManagementTest, IsVehicleCurrentlyRented_True) {
    EXPECT_TRUE(rentalManagement.isVehicleCurrentlyRented(vehicle1));
}

TEST_F(RentalManagementTest, IsVehicleCurrentlyRented_False) {
    EXPECT_FALSE(rentalManagement.isVehicleCurrentlyRented(vehicle2));
}

TEST_F(RentalManagementTest, IsCustomerCurrentlyRenting_Null) {
    EXPECT_FALSE(rentalManagement.isCustomerCurrentlyRenting(nullptr));
}

TEST_F(RentalManagementTest, IsVehicleCurrentlyRented_Null) {
    EXPECT_FALSE(rentalManagement.isVehicleCurrentlyRented(nullptr));
}

TEST_F(RentalManagementTest, GetRentals) {
    rentalManagement.openRental(rental2);

    std::vector<Rental*> expectedRentals = {rental1, rental2};
    EXPECT_EQ(rentalManagement.getRentals(), expectedRentals);
}

TEST_F(RentalManagementTest, GetCurrentCustomers) {
    rentalManagement.openRental(rental2);

    std::vector<Customer*> expectedCustomers = {customer1, customer2};
    EXPECT_EQ(rentalManagement.getCurrentCustomers(), expectedCustomers);
}

TEST_F(RentalManagementTest, CreateAndCloseRental) {
    rentalManagement.openRental(rental2);

    EXPECT_NE(rentalManagement.getRental("1"), nullptr);
    EXPECT_NE(rentalManagement.getRental("2"), nullptr);
    EXPECT_EQ(rentalManagement.getRental("3"), nullptr);

    EXPECT_EQ(rentalManagement.getRental("1")->getCustomer()->getFirstName(), "John");
    EXPECT_EQ(rentalManagement.getRental("2")->getCustomer()->getFirstName(), "Jane");

    rentalManagement.closeRental("2");
    EXPECT_EQ(rentalManagement.getRental("2"), nullptr);
}

TEST_F(RentalManagementTest, RentUnavailableVehicle)
{
    Location location(1, "Main Office", nullptr);
    vehicle1->updateLocation(&location);

    EXPECT_THROW(rentalManagement.openRental(new Rental("R004", customer1, vehicle1, 2)), std::invalid_argument);

    EXPECT_EQ(rentalManagement.getRental("R004"), nullptr);
}

TEST_F(RentalManagementTest, RentAndReturnToDifferentLocation)
{
    Location pickupLocation(1, "Pickup Location", address1);
    vehicle1->updateLocation(&pickupLocation);

    rentalManagement.openRental(rental2);

    Location dropoffLocation(3, "Dropoff Location", address2);
    vehicle1->updateLocation(&dropoffLocation);

    rentalManagement.closeRental("R005");

    EXPECT_EQ(rentalManagement.getRental("R005"), nullptr);
}

TEST_F(RentalManagementTest, CustomerTriesToRentSecondVehicle)
{
    Address *address3 = new Address("id3", "123 Street", "City", "State", "12345");
    Location pickupLocation(1, "Pickup Location", address3);
    Vehicle *vehicle3 = new Vehicle("V100", "JKL124", "Ford", "Escape", 2020, "Silver", "Automatic", "Petrol", 5, true, 60.0);
    vehicle3->updateLocation(&pickupLocation);
    Rental *rental3 = new Rental("3", customer1, vehicle3, 4);
    EXPECT_TRUE(rentalManagement.openRental(rental2));
    EXPECT_FALSE(rentalManagement.openRental(rental3));
}

TEST_F(RentalManagementTest, CurrentCustomers)
{
    std::vector<Customer *> customers = {customer1, customer2};

    EXPECT_EQ(rentalManagement.getCurrentCustomers().size(), 1);
    EXPECT_TRUE(rentalManagement.openRental(rental2));

    EXPECT_EQ(rentalManagement.getCurrentCustomers().size(), 2);
    EXPECT_EQ(rentalManagement.getCurrentCustomers(), customers);
}

TEST_F(RentalManagementTest, RentalsToBeTerminated)
{
    std::chrono::system_clock::time_point time_after_an_hour = std::chrono::system_clock::now() + std::chrono::hours(1);
    std::chrono::system_clock::time_point time_after_seven_hours = std::chrono::system_clock::now() + std::chrono::hours(7);
    std::chrono::system_clock::time_point time_after_ten_hours = std::chrono::system_clock::now() + std::chrono::hours(10);

    rentalManagement.openRental(rental2);

    auto rentalsToBeTerminated = rentalManagement.getRentalsToBeTerminated(time_after_an_hour);
    EXPECT_EQ(rentalsToBeTerminated.size(), 0);

    rentalsToBeTerminated = rentalManagement.getRentalsToBeTerminated(time_after_seven_hours);
    EXPECT_EQ(rentalsToBeTerminated.size(), 1);
    EXPECT_EQ(rentalsToBeTerminated[0]->getId(), "1");

    rentalsToBeTerminated = rentalManagement.getRentalsToBeTerminated(time_after_ten_hours);
    EXPECT_EQ(rentalsToBeTerminated.size(), 2);
    EXPECT_EQ(rentalsToBeTerminated[0]->getId(), "1");
    EXPECT_EQ(rentalsToBeTerminated[1]->getId(), "2");
}