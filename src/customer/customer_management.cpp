#include "customer_management.h"

bool CustomerManagement::addCustomer(Customer *customer)
{
    // check if the customer is already in the list use the find_if method
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *c)
                           { return c->getId() == customer->getId(); });

    // if the customer is not in the list, add it
    if (it == customers.end())
    {
        customers.push_back(customer);
        return true;
    }

    // else std::cout << "Customer with id " << customer->getId() << " already exists." << std::endl;
    else
        return false;
}

bool CustomerManagement::removeCustomer(const std::string id)
{
    // iterator that points to the customer to be removed
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *customer)
                           { return customer->getId() == id; });

    if (it != customers.end())
    {
        // Remove the customer
        // delete *it;
        customers.erase(it);
        return true;

        // *it = nullptr;
    }
    else
    {
        // Handle the case where the customer was not found
        // std::cout << "Customer with id " << id << " not found." << std::endl;
        return false;
    }
}

Customer *CustomerManagement::getCustomer(std::string id) const
{
    auto it = std::find_if(customers.begin(), customers.end(), [&](Customer *customer)
                           { return customer->getId() == id; });
    // if the customer is found, return it
    if (it != customers.end())
    {
        return *it;
    }

    return nullptr;
}
