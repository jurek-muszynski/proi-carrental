#pragma once

#include <string>
#include <vector>
#include "rental.h"

class RentalManagement
{
private:
    std::vector<std::shared_ptr<Rental>> rentals; // Use std::shared_ptr<Rental> instead of Rental*

public:
    const std::shared_ptr<Rental> getRental(const std::string& id) const;
    std::shared_ptr<Rental> getRentalByVehicleId(const std::string& id) const;
    const std::vector<std::shared_ptr<Rental>> getRentals() const;

    const std::vector<std::shared_ptr<Customer>> getCurrentCustomers() const;
    const std::vector<std::shared_ptr<Vehicle>> getCurrentVehicles() const;
    const std::vector<std::shared_ptr<Rental>> getRentalsToBeTerminated(std::chrono::system_clock::time_point current_time) const;

    bool isCustomerCurrentlyRenting(std::shared_ptr<Customer> customer) const;
    bool isVehicleCurrentlyRented(std::shared_ptr<Vehicle> vehicle) const;
    bool openRental(std::shared_ptr<Rental> rental);
    bool closeRental(const std::string& id);
};