#pragma once

#include <string>
#include <vector>
#include "rental.h"

class RentalManagement
{
private:
    std::vector<Rental *> rentals;

public:
    const Rental *getRental(const std::string id) const;
    Rental *getRentalByVehicleId(const std::string id) const;
    const std::vector<Rental *> getRentals() const;

    const std::vector<Customer *> getCurrentCustomers() const;
    const std::vector<Vehicle *> getCurrentVehicles() const;
    const std::vector<Rental *> getRentalsToBeTerminated(std::chrono::system_clock::time_point current_time) const;

    bool isCustomerCurrentlyRenting(Customer *customer) const;
    bool isVehicleCurrentlyRented(Vehicle *vehicle) const;
    bool openRental(Rental *rental);
    bool closeRental(const std::string id);
};