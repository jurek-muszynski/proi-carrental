#include "customer_management.h"

const Customer *CustomerManagement::getCustomer(std::string id) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer *customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        return *it;
    }

    return nullptr;
}

const std::vector<const Customer *> CustomerManagement::getCustomers() const
{
    return customers;
}

size_t CustomerManagement::getCustomerCount() const
{
    return customers.size();
}

bool CustomerManagement::isCustomerAlreadyRegistered(const Customer *customer) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer *c)
                           { return c->getId() == customer->getId(); });

    return it != customers.end();
}

bool CustomerManagement::addCustomer(const Customer *customer)
{
    if (!isCustomerAlreadyRegistered(customer))
    {
        customers.push_back(customer);
        return true;
    }

    return false;
}

bool CustomerManagement::removeCustomer(const std::string id)
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer *customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        customers.erase(it);
        return true;
    }

    return false;
}
