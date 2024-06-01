#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "customer.h"

class CustomerManagement
{
private:
    std::vector<Customer *> customers;

public:
    Customer *getCustomer(const std::string id) const;

    bool addCustomer(Customer *customer);
    bool removeCustomer(const std::string id);
};