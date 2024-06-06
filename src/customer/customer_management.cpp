#include "customer_management.h"

Customer *CustomerManagement::getCustomer(std::string id) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer *customer)
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

bool CustomerManagement::isCustomerAlreadyRegistered(const Customer *customer) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *c)
                           { return c->getId() == customer->getId(); });

    return it != customers.end();
}

bool CustomerManagement::addCustomer(Customer *customer)
{
    if (!isCustomerAlreadyRegistered(customer) and customer != nullptr)
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
