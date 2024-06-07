#include "gtest/gtest.h"
#include "../src/customer/customer.h"

TEST(CustomerTest, GettersAndSetters)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    customer->updatePhoneNumber("0987654321");
    customer->updateEmail("doe.john@example.com");
    std::shared_ptr<Address> new_address = std::make_shared<Address>("id2", "321 Avenue", "Town", "Province", "54321");
    customer->updateAddress(new_address);

    EXPECT_EQ(customer->getFirstName(), "John");
    EXPECT_EQ(customer->getLastName(), "Doe");
    EXPECT_EQ(customer->getGender(), "Male");
    EXPECT_EQ(customer->getEmail(), "doe.john@example.com");
    EXPECT_EQ(customer->getPhoneNumber(), "0987654321");
    EXPECT_EQ(customer->getAddress()->getStreet(), "321 Avenue");
    EXPECT_EQ(customer->getAddress()->getCity(), "Town");
    EXPECT_EQ(customer->getAddress()->getCountry(), "Province");
    EXPECT_EQ(customer->getAddress()->getZipCode(), "54321");
}

TEST(CustomerTest, Destructor)
{
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    std::shared_ptr<Address> address = std::make_shared<Address>("id1", "123 Street", "City", "State", "12345");
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    customer.reset();
    EXPECT_EQ(customer, nullptr);
}