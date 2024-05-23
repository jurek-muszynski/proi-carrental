#include "customer_managment.h"

void CustomerManagement::addCustomer(Customer *customer)
{
    customers.push_back(customer);
}

void CustomerManagement::removeCustomer(Customer *customer)
{
    for (int i = 0; i < customers.size(); i++) {
    if (customers[i]->getId() == customer->getId()) {
        delete customers[i];
        customers.erase(customers.begin() + i);
        break;
    }
    }
}

Customer *CustomerManagement::getCustomer(std::string id)
{
    return nullptr;
}
