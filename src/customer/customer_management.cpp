#include "customer_management.h"

Customer *CustomerManagement::getCustomer(std::string id) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        return *it;
    }

    return nullptr;
}

std::vector<Customer *> CustomerManagement::getCustomers() const
{
    return customers;
}

size_t CustomerManagement::getCustomerCount() const
{
    return customers.size();
}

bool CustomerManagement::addCustomer(Customer *customer)
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *c)
                           { return c->getId() == customer->getId(); });

    if (it == customers.end())
    {
        customers.push_back(customer);
        return true;
    }

    return false;
}

bool CustomerManagement::removeCustomer(const std::string id)
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        customers.erase(it);
        return true;
    }

    return false;
}
