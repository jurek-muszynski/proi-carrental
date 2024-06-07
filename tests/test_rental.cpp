#include "gtest/gtest.h"
#include "../src/rental/rental.h"

TEST(RentalTest, CalculateCost)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);

    EXPECT_EQ(vehicle->getRentalRates(), 100.0);
    EXPECT_EQ(rental.getDuration(), 7);
    EXPECT_EQ(rental.calculateCost(), 700.0);
}

TEST(RentalTest, GetId)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);
    EXPECT_EQ(rental.getId(), "1");
}

TEST(RentalTest, GetCustomer)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);
    EXPECT_EQ(rental.getCustomer(), customer);
}

TEST(RentalTest, GetVehicle)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);
    EXPECT_EQ(rental.getVehicle(), vehicle);
}

TEST(RentalTest, Destructor)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental *rental = new Rental("1", customer, vehicle, 7);
    delete rental;
    EXPECT_EQ(rental->getCustomer(), nullptr);
    EXPECT_EQ(rental->getVehicle(), nullptr);
}

TEST(RentalTest, RentalWithUnavailableVehicle)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "City", "State", "12345");
    Customer *customer = new Customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Vehicle *vehicle = new Vehicle("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, false, 100.0);
    EXPECT_THROW({ Rental("1", customer, vehicle, 3); }, std::invalid_argument);
    delete customer;
    delete vehicle;
}

TEST(RentalTest, SetDropOffLocation) {
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;

    Address* address1 = new Address("5", "123 Main St", "Springfield", "USA", "12345", 23.15, 53.1333);
    Address* address2 = new Address("6", "456 Elm St", "Shelbyville", "USA", "67890", 21.00, 52.13);
    
    Customer *customer = new Customer("id1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address1);
    
    Location pickUpLocation(1, "Location1", address1);
    Location dropOffLocation(2, "Location2", address2);

    Vehicle* vehicle = new Vehicle("V1", "XYZ123", "Toyota", "Camry", 2020, "Red", "Automatic", "Gasoline", 5, true, 50.0);
    vehicle->updateLocation(&pickUpLocation);
    Rental* rental = new Rental("1", customer, vehicle, 7);

    rental->setDropOffLocation(&dropOffLocation);

    EXPECT_EQ(vehicle->getLocation(), &dropOffLocation);
}