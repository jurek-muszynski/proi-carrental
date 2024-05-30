#pragma once

#include "customer.h"
#include <vector>
#include <string>

class CustomerManagement
{
private:
    std::vector<Customer *> customers;

public:
    void addCustomer(Customer *customer);
    void removeCustomer(Customer *customer);
    Customer *getCustomer(std::string id);
};