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

    const std::vector<const Customer *> getCurrentCustomers() const;
    const std::vector<const Rental *> getRentalsToBeTerminated(std::chrono::system_clock::time_point current_time) const;

    bool isCustomerCurrentlyRenting(const Customer *customer) const;
    bool openRental(const Rental *rental);
    bool closeRental(const std::string id);
};