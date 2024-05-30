// #include "gtest/gtest.h"
// #include "../src/customer/customer.h"

// TEST(CustomerTest, GettersAndSetters)
// {
//     std::tm birthDate = {};
//     birthDate.tm_year = 1990 - 1900;
//     birthDate.tm_mon = 1 - 1;
//     birthDate.tm_mday = 1;
//     Address address("id1", "123 Street", "City", "State", "12345");
//     Customer customer("1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
//     customer.updatePhoneNumber("0987654321");
//     customer.updateEmail("doe.john@example.com");
//     Address new_address("id2", "321 Avenue", "Town", "Province", "54321");
//     customer.updateAddress(new_address);

//     EXPECT_EQ(customer.getFirstName(), "John");
//     EXPECT_EQ(customer.getLastName(), "Doe");
//     EXPECT_EQ(customer.getGender(), "Male");
//     EXPECT_EQ(customer.getEmail(), "doe.john@example.com");
//     EXPECT_EQ(customer.getPhoneNumber(), "0987654321");
//     EXPECT_EQ(customer.getAddress().getStreet(), "321 Avenue");
//     EXPECT_EQ(customer.getAddress().getCity(), "Town");
//     EXPECT_EQ(customer.getAddress().getCountry(), "Province");
//     EXPECT_EQ(customer.getAddress().getZipCode(), "54321");
// }