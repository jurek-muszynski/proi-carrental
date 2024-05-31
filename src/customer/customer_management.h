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
    void addCustomer(Customer *customer);
    void removeCustomer(const std::string id);
    Customer *getCustomer(const std::string id) const;
};