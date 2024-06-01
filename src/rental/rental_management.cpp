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

bool RentalManagement::openRental(const Rental *rental)
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
