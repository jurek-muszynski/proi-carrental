#include "rental_management.h"
#include <algorithm>

Rental *RentalManagement::getRental(std::string id) const
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](Rental *rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        return *it;
    }
    return nullptr;
}

void RentalManagement::openRental(Rental *rental)
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](Rental *r)
                           { return r->getId() == rental->getId(); });

    if (it == rentals.end())
        rentals.push_back(rental);
    else
        std::cout << "Rental with id " << rental->getId() << " has already been opened." << std::endl;
}

void RentalManagement::closeRental(const std::string id)
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](Rental *rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        rentals.erase(it);
    }
    else
    {
        std::cout << "Rental with id " << id << " not found." << std::endl;
    }
}
