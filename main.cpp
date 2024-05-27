#include <iostream>
#include "src/customer/customer.h"

int main()
{
    // SAMPLE DEMO
    std::tm birthDate = {};
    birthDate.tm_year = 1990-1900; // years since 1900
    birthDate.tm_mon = 12-1; // months since January (0-11)
    birthDate.tm_mday = 25; // day of the month (1-31)

    Address address("1", "123 Main St", "New York", "NY", "10001");

    Customer customer("1", "John", "Doe", birthDate, "Male", "johndoe@example.com", "1234567890", address);

    std::cout << customer.getId() << std::endl;
    std::cout << customer.getFname() << std::endl;
    std::cout << customer.getLname() << std::endl;
    std::cout << customer.getBirthDate() << std::endl;
    std::cout << customer.getGender() << std::endl;
    std::cout << customer.getEmail() << std::endl;
    std::cout << customer.getPhoneNumber() << std::endl;
    std::cout << customer.getAddress().getId() << std::endl;
    std::cout << customer.getAddress().getStreet() << std::endl;
    std::cout << customer.getAddress().getCity() << std::endl;
    std::cout << customer.getAddress().getState() << std::endl;
    std::cout << customer.getAddress().getZipCode() << std::endl;
    
    return 0;
}