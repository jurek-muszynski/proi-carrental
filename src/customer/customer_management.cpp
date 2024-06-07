#include "customer_management.h"

std::shared_ptr<Customer> CustomerManagement::getCustomer(const std::string &id) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const std::shared_ptr<Customer> &customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        return *it;
    }

    return nullptr;
}

std::vector<std::shared_ptr<Customer>> CustomerManagement::getCustomers() const
{
    return customers;
}

size_t CustomerManagement::getCustomerCount() const
{
    return customers.size();
}

bool CustomerManagement::isCustomerAlreadyRegistered(const std::shared_ptr<Customer> customer) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const std::shared_ptr<Customer> &c)
                           { return c->getId() == customer->getId(); });

    return it != customers.end();
}

bool CustomerManagement::addCustomer(const std::shared_ptr<Customer> customer)
{
    if (!isCustomerAlreadyRegistered(customer))
    {
        customers.push_back(customer);
        return true;
    }

    return false;
}

bool CustomerManagement::removeCustomer(const std::string &id)
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](const std::shared_ptr<Customer> &customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        customers.erase(it);
        return true;
    }

    return false;
}
