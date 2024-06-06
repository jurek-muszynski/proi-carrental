#pragma once

#include <chrono>
#include <iomanip>
#include <string>
#include "../vehicle/vehicle.h"
#include "../customer/customer.h"

class Rental
{
private:
    std::string id;
    Customer *customer;
    Vehicle *vehicle;
    Location *pickupLocation;
    Location *dropOffLocation = nullptr;
    int duration;
    double rate;
    std::chrono::system_clock::time_point rent_time;
    std::chrono::system_clock::time_point return_time;

public:
    Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration, std::chrono::system_clock::time_point rent_time = std::chrono::system_clock::now());
    ~Rental();

    double calculateCost() const;
    double calculateDistance() const;
    int getDuration() const;
    std::string getId() const;
    Customer *getCustomer() const;
    Vehicle *getVehicle() const;
    std::chrono::system_clock::time_point getRentTime() const;
    std::chrono::system_clock::time_point getReturnTime() const;

    void printReturnTime() const;
    void printRentTime() const;

    void setDropOffLocation(Location *location);

    friend std::ostream &operator<<(std::ostream &os, const Rental &rental);
};
