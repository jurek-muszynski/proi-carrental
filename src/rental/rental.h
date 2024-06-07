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
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<Location> pickupLocation;
    std::shared_ptr<Location> dropOffLocation = nullptr;
    int duration;
    double rate;
    std::chrono::system_clock::time_point rent_time;
    std::chrono::system_clock::time_point return_time;

public:
    Rental(std::string id, std::shared_ptr<Customer> customer, std::shared_ptr<Vehicle> vehicle, int duration, std::chrono::system_clock::time_point rent_time = std::chrono::system_clock::now());
    ~Rental();

    double calculateCost() const;
    double calculateDistance() const;
    int getDuration() const;
    std::string getId() const;
    std::shared_ptr<Customer> getCustomer() const;
    std::shared_ptr<Vehicle> getVehicle() const;
    std::chrono::system_clock::time_point getRentTime() const;
    std::chrono::system_clock::time_point getReturnTime() const;

    void printReturnTime() const;
    void printRentTime() const;

    void setDropOffLocation(std::shared_ptr<Location> location);

    friend std::ostream &operator<<(std::ostream &os, const Rental &rental);
};
