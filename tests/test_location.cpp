#include <gtest/gtest.h>
#include "../src/location/location.h"

TEST(LocationTest, ConstructorAndGetters)
{
    std::shared_ptr<Address> address = std::make_shared<Address>("1", "123 Main St", "Springfield", "USA", "12345");
    Location location(101, "Main Office", address);

    EXPECT_EQ(location.getLocationId(), 101);
    EXPECT_EQ(location.getName(), "Main Office");
    EXPECT_EQ(location.getAddress()->getId(), "1");
}

TEST(LocationTest, NullAddress)
{
    Location location(102, "Unknown Location", nullptr);

    EXPECT_EQ(location.getLocationId(), 102);
    EXPECT_EQ(location.getName(), "Unknown Location");
}

TEST(LocationTest, ConsistentAddressReference)
{
    std::shared_ptr<Address> address = std::make_shared<Address>("2", "456 Elm St", "Shelbyville", "USA", "67890");
    Location location(103, "Secondary Office", address);

    EXPECT_EQ(location.getAddress()->getId(), "2");
    EXPECT_EQ(location.getAddress()->getStreet(), "456 Elm St");
    EXPECT_EQ(location.getAddress()->getCity(), "Shelbyville");
    EXPECT_EQ(location.getAddress()->getCountry(), "USA");
    EXPECT_EQ(location.getAddress()->getZipCode(), "67890");
}

TEST(LocationTest, MultipleLocationsSameAddress)
{
    std::shared_ptr<Address> address = std::make_shared<Address>("3", "789 Oak St", "Capital City", "USA", "10101");
    Location location1(104, "Branch Office", address);
    Location location2(105, "Warehouse", address);

    EXPECT_EQ(location1.getAddress()->getId(), location2.getAddress()->getId());
    EXPECT_EQ(location1.getAddress()->getStreet(), location2.getAddress()->getStreet());
    EXPECT_EQ(location1.getAddress()->getCity(), location2.getAddress()->getCity());
    EXPECT_EQ(location1.getAddress()->getCountry(), location2.getAddress()->getCountry());
    EXPECT_EQ(location1.getAddress()->getZipCode(), location2.getAddress()->getZipCode());
}

TEST(LocationTest, Destructor)
{
    std::shared_ptr<Address> address = std::make_shared<Address>("4", "123 Main St", "Springfield", "USA", "12345");
    std::shared_ptr<Location> location = std::make_unique<Location>(106, "Main Office", address);
    EXPECT_EQ(location->getAddress(), address);
    location.reset();
    EXPECT_EQ(location, nullptr);
}

TEST(LocationTest, CalculateDistance)
{
    std::shared_ptr<Address> address1 = std::make_shared<Address>("5", "123 Main St", "Springfield", "USA", "12345", 23.15, 53.1333);
    Location location1(107, "Main Office", address1);
    std::shared_ptr<Address> address2 = std::make_shared<Address>("6", "456 Elm St", "Shelbyville", "USA", "67890", 21.00, 52.13);
    Location location2(108, "Secondary Office", address2);

    double distance = location1.calculateDistance(location2);
    EXPECT_NEAR(distance, 183.0, 5.0);
}

TEST(LocationTest, CalculateDistanceNullAddress)
{
    std::shared_ptr<Address> address1 = std::make_shared<Address>("5", "123 Main St", "Springfield", "USA", "12345", 23.15, 53.1333);
    Location location1(1, "Location1", address1);

    Location location2(2, "Location2", nullptr);

    EXPECT_THROW(location1.calculateDistance(location2), std::invalid_argument);
}

TEST(LocationTest, OperatorStreamInsertion)
{
    std::shared_ptr<Address> address1 = std::make_shared<Address>("5", "123 Main St", "Springfield", "USA", "12345");

    Location location(106, "Main Office", address1);

    std::ostringstream os;
    os << location;
    EXPECT_EQ(os.str(), "Location ID: 106 Name: Main Office\n\tAddress: 123 Main St Street Springfield");
}

TEST(LocationTest, OperatorStreamInsertionNullAddress)
{
    Location location(106, "Main Office", nullptr);

    std::ostringstream os;
    os << location;
    EXPECT_EQ(os.str(), "Location ID: 106 Name: Main Office");
}