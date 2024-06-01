#pragma once

#include <string>
#include <vector>
#include "rental.h"

class RentalManagement
{
private:
    std::vector<const Rental *> rentals;

public:
    const Rental *getRental(const std::string id) const;

    bool openRental(const Rental *rental);
    bool closeRental(const std::string id);
};