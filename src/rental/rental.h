#pragma once

#include "../vehicle/vehicle.h"
#include "../customer/customer.h"
#include <string>

class Rental
{
public:
    Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration);
    double calculateCost() const;
    std::string getId() const;
    Customer *getCustomer() const;
    Vehicle *getVehicle() const;
    int getDuration() const;

    // destructor
    ~Rental();

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
    static double rate;
};
