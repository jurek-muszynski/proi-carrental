#pragma once

#include <string>
#include "../vehicle/vehicle.h"
#include "../customer/customer.h"

class Rental
{
private:
    std::string id;
    Customer *customer;
    Vehicle *vehicle;
    // std::string pickupLocation;
    // std::string dropoffLocation;
    // std::string rentalStartDate;
    // std::string rentalEndDate;
    int duration;
    // double totalCharges;
    double rate;

public:
    Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration);
    ~Rental();

    double calculateCost() const;
    int getDuration() const;
    std::string getId() const;
    Customer *getCustomer() const;
    Vehicle *getVehicle() const;
};
