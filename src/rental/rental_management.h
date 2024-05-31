#pragma once

#include "rental.h"
#include <string>
#include <vector>

class RentalManagement
{
private:
    std::vector<Rental *> rentals;

public:
    void openRental(Rental *rental);
    void closeRental(const std::string id);
    Rental *getRental(const std::string id) const;
};