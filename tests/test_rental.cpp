#include "gtest/gtest.h"
#include "../src/rental/rental.h"

TEST(RentalTest, CalculateCost)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);

    EXPECT_EQ(vehicle->getRentalRates(), 100.0);
    EXPECT_EQ(rental.getDuration(), 7);
    EXPECT_EQ(rental.calculateCost(), 700.0);
}

// test the destructor of Rental
TEST(RentalTest, GetId)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);
    EXPECT_EQ(rental.getId(), "1");
}

TEST(RentalTest, GetCustomer)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);
    EXPECT_EQ(rental.getCustomer(), customer);
}

TEST(RentalTest, GetVehicle)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    Rental rental("1", customer, vehicle, 7);
    EXPECT_EQ(rental.getVehicle(), vehicle);
}

TEST(RentalTest, Destructor)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, true, 100.0);
    auto rental = std::make_shared<Rental>("1", customer, vehicle, 7);
    rental.reset();
    EXPECT_EQ(rental, nullptr);
}

TEST(RentalTest, RentalWithUnavailableVehicle)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    auto address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    auto customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    auto vehicle = std::make_shared<Vehicle>("1", "ABC123", "Toyota", "Corolla", 2020, "White", "Automatic", "Gasoline", 5, false, 100.0);
    EXPECT_THROW({ Rental("1", customer, vehicle, 3); }, std::invalid_argument);
}
