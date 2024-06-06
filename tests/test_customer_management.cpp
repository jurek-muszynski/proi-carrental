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

TEST(CustomerManagementTest, GetCustomers) {
    CustomerManagement cm;

    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "Country", "City", "12345");

    birthDate.tm_year = 1991 - 1900;
    birthDate.tm_mon = 2 - 1;
    birthDate.tm_mday = 2;
    Address *address2 = new Address("id2", "321 Avenue", "Country", "City", "54321");
    Customer *customer1 = new Customer("id1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    Customer *customer2 = new Customer("id2", "Jane", "Doe", birthDate, "Female", "jane.doe@example.com", "0987654321", address2);
    cm.addCustomer(customer1);
    cm.addCustomer(customer2);

    std::vector<Customer*> customers = cm.getCustomers();

    EXPECT_EQ(customers.size(), 2);
    EXPECT_EQ(customers[0], customer1);
    EXPECT_EQ(customers[1], customer2);

    delete customer1;
    delete customer2;
}

TEST(CustomerManagementTest, AddSameCustomer)
{
    CustomerManagement customerManagement;
    std::tm birthDate = {};
    birthDate.tm_year = 1990 - 1900;
    birthDate.tm_mon = 1 - 1;
    birthDate.tm_mday = 1;
    Address *address = new Address("id1", "123 Street", "Country", "City", "12345");
    Customer *customer1 = new Customer("id1", "John", "Doe", birthDate, "Male", "john.doe@example.com", "1234567890", address);
    EXPECT_TRUE(customerManagement.addCustomer(customer1));
    EXPECT_NE(customerManagement.getCustomer("id1"), nullptr);
    EXPECT_EQ(customerManagement.getCustomer("id1"), customer1);
    EXPECT_EQ(customerManagement.getCustomer("id1")->getFirstName(), "John");

    EXPECT_FALSE(customerManagement.addCustomer(customer1));
    EXPECT_EQ(customerManagement.getCustomer("id1"), customer1);
    EXPECT_EQ(customerManagement.getCustomer("id1")->getFirstName(), "John");
}

TEST(CustomerManagementTest, AddNullCustomer) {
    CustomerManagement cm;

    EXPECT_FALSE(cm.addCustomer(nullptr));
    EXPECT_EQ(cm.getCustomerCount(), 0);
}

TEST(CustomerManagementTest, NonExistentCustomer) {
    CustomerManagement cm;

    EXPECT_EQ(cm.getCustomer("1"), nullptr);

    EXPECT_FALSE(cm.removeCustomer("1"));
}