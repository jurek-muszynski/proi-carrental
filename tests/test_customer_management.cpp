#include "gtest/gtest.h"
#include "../src/customer/customer_management.h"

TEST(CustomerManagementTest, AddAndRemoveCustomer)
{
    CustomerManagement customerManagement;
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "Country", "City", "12345");
    Customer *customer1 = new Customer("id1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    customerManagement.addCustomer(customer1);

    birthDate.tm_year = 1991 - 1900;
    birthDate.tm_mon = 2 - 1;
    birthDate.tm_mday = 2;
    Address *address2 = new Address("id2", "321 Avenue", "Country", "City", "54321");
    Customer *customer2 = new Customer("id2", "Jane", "Doe", birthDate, "Female", "jane.doe@example.com", "0987654321", address2);
    customerManagement.addCustomer(customer2);

    EXPECT_NE(customerManagement.getCustomer("id1"), nullptr);
    EXPECT_NE(customerManagement.getCustomer("id2"), nullptr);
    EXPECT_EQ(customerManagement.getCustomer("id3"), nullptr);
    EXPECT_EQ(customerManagement.getCustomer("id1"), customer1);
    EXPECT_EQ(customerManagement.getCustomer("id2"), customer2);
    EXPECT_EQ(customerManagement.getCustomer("id1")->getFirstName(), "John");
    EXPECT_EQ(customerManagement.getCustomer("id2")->getFirstName(), "Jane");

    customerManagement.removeCustomer(customer2->getId());
    EXPECT_EQ(customerManagement.getCustomer("2"), nullptr);
}