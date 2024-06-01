#pragma once

#include "customer.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class CustomerManagement
{
private:
    std::vector<Customer *> customers;

public:
    bool addCustomer(Customer *customer);
    bool removeCustomer(const std::string id);
    Customer *getCustomer(const std::string id) const;
};