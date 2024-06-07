#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "customer.h"

class CustomerManagement
{
private:
    std::vector<std::shared_ptr<Customer>> customers;

public:
    std::shared_ptr<Customer> getCustomer(const std::string &id) const;
    std::vector<std::shared_ptr<Customer>> getCustomers() const;

    size_t getCustomerCount() const;

    bool isCustomerAlreadyRegistered(const std::shared_ptr<Customer> customer) const;
    bool addCustomer(std::shared_ptr<Customer> customer);
    bool removeCustomer(const std::string &id);
};