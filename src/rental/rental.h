#pragma once

#include <chrono>
#include <string>
#include "../vehicle/vehicle.h"
#include "../customer/customer.h"

class Rental
{
private:
    std::string id;
    const Customer *customer;
    Vehicle *vehicle;
    const Location *pickupLocation;
    Location *dropoffLocation = nullptr;
    int duration;
    // double totalCharges;
    double rate;
    std::chrono::system_clock::time_point rent_time;

public:
    Rental(std::string id, const Customer *customer, Vehicle *vehicle, int duration, std::chrono::system_clock::time_point rent_time = std::chrono::system_clock::now());
    ~Rental();

    double calculateCost() const;
    int getDuration() const;
    std::string getId() const;
    const Customer *getCustomer() const;
    Vehicle *getVehicle() const;
    std::chrono::system_clock::time_point getRentTime() const;

    void setDropoffLocation(Location *location);

    friend std::ostream &operator<<(std::ostream &os, const Rental &rental);
};
