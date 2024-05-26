#include <iostream>
#include "src/customer/customer.h"

int main()
{
    // SAMPLE DEMO

    Customer c1("1", "John Doe", "123-456-7890");

    std::cout << c1.getName() << std::endl;

    return 0;
}