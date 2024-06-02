#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "customer.h"

class CustomerManagement
{
private:
    std::vector<const Customer *> customers;

public:
    const Customer *getCustomer(const std::string id) const;
    const std::vector<const Customer *> getCustomers() const;

    size_t getCustomerCount() const;

    bool isCustomerAlreadyRegistered(const Customer *customer) const;
    bool addCustomer(const Customer *customer);
    bool removeCustomer(const std::string id);
};