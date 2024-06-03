#include "rental_management.h"
#include <algorithm>

const Rental *RentalManagement::getRental(std::string id) const
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const Rental *rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        return *it;
    }
    return nullptr;
}

const std::vector< Customer *> RentalManagement::getCurrentCustomers() const
{
    std::vector< Customer *> customers;
    for ( Rental *rental : rentals)
    {
        customers.push_back(rental->getCustomer());
    }
    return customers;
}

const std::vector<Rental *> RentalManagement::getRentalsToBeTerminated(std::chrono::system_clock::time_point current_time) const
{
    std::vector<Rental *> rentalsToBeTerminated;

    for (Rental *rental : rentals)
    {
        if (rental->getRentTime() + std::chrono::hours(rental->getDuration()) <= current_time)
        {
            rentalsToBeTerminated.push_back(rental);
        }
    }
    return rentalsToBeTerminated;
}

bool RentalManagement::isCustomerCurrentlyRenting(Customer *customer) const
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const Rental *rental)
                           { return rental->getCustomer()->getId() == customer->getId(); });

    return it != rentals.end();
}

bool RentalManagement::openRental(Rental *rental)
{
    auto rentalIndexIterator = std::find_if(rentals.begin(), rentals.end(), [&](const Rental *r)
                                            { return r->getId() == rental->getId(); });

    auto customerIndexIterator = std::find_if(rentals.begin(), rentals.end(), [&](const Rental *r)
                                              { return r->getCustomer()->getId() == rental->getCustomer()->getId(); });

    if (rentalIndexIterator == rentals.end() && customerIndexIterator == rentals.end())
    {
        rentals.push_back(rental);
        return true;
    }
    return false;
}

bool RentalManagement::closeRental(const std::string id)
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const Rental *rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        rentals.erase(it);
        return true;
    }
    return false;
}
