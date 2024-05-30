#include "rental_management.h"
#include <algorithm>

void RentalManagement::openRental(Rental *rental)
{
    rentals.push_back(rental);
}

void RentalManagement::closeRental(const std::string id)
{
    // iterator that points to the rental to be closed
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](Rental *rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        // Close the rental
        delete *it;
        rentals.erase(it);

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
    for (Rental *rental : rentals)
    {
        if (rental->getId() == id)
        {
            return rental;
        }
    }
    return nullptr;
}