#pragma once

#include <iomanip>
#include <map>
#include <sstream>
#include <vector>

#include "../rental/rental.h"

class SimulationReport
{
private:
    struct CustomerData
    {
        int rentalCount = 0;
        double totalCost = 0;
        double totalDuration = 0;
    };

    std::map<Customer *, CustomerData> customerRentals;

public:
    void addRentalData(const Rental *rental);
    void generateSummary() const;
};