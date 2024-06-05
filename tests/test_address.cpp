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