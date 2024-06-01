#pragma once

#include <string>
#include <vector>
#include "rental.h"

class RentalManagement
{
private:
    std::vector<Rental *> rentals;

public:
    Rental *getRental(const std::string id) const;

    void openRental(Rental *rental);
    void closeRental(const std::string id);
};