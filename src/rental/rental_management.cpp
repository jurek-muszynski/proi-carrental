#include "rental_management.h"
#include <algorithm>

void RentalManagement::openRental(Rental *rental)
{
    // check if the rental has already been opened
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](Rental *r)
                           { return r->getId() == rental->getId(); });

    // if the rental is not in the list, add it
    if (it == rentals.end())
        rentals.push_back(rental);
    else
        std::cout << "Rental with id " << rental->getId() << " has already been opened." << std::endl;
}

void RentalManagement::closeRental(const std::string id)
{
    // iterator that points to the rental to be closed
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](Rental *rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        // Close the rental
        rentals.erase(it);
        // delete *it;
        // *it = nullptr;
    }
    else
    {
        // Handle the case where the rental was not found
        std::cout << "Rental with id " << id << " not found." << std::endl;
    }
}

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