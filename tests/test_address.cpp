#include <gtest/gtest.h>
#include "../src/address/address.h"

TEST(AddressTest, ConstructorAndGetters)
{
    Address address("1", "123 Main St", "Springfield", "USA", "12345", 0.0, 0.0);

    EXPECT_EQ(address.getId(), "1");
    EXPECT_EQ(address.getStreet(), "123 Main St");
    EXPECT_EQ(address.getCity(), "Springfield");
    EXPECT_EQ(address.getCountry(), "USA");
    EXPECT_EQ(address.getZipCode(), "12345");
}

TEST(AddressTest, PrintOperator) {
    Address address("1", "Main St", "City", "Country", "12345", 12.34, 56.78);
    std::ostringstream os;
    os << address;

    EXPECT_EQ(os.str(), "Address: Main St Street City");
}

TEST(AddressTest, InvalidLongitude)
{
    try {
        Address address("1", "123 Main St", "Springfield", "USA", "12345", -200.0, 0.0);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(const std::invalid_argument& err) {
        EXPECT_EQ(err.what(), std::string("Invalid longitude"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(AddressTest, InvalidLatitude)
{
    try {
        Address address("1", "123 Main St", "Springfield", "USA", "12345", 0.0, -200.0);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(const std::invalid_argument& err) {
        EXPECT_EQ(err.what(), std::string("Invalid latitude"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}