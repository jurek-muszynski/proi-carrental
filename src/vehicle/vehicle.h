#pragma once

#include <iostream>
#include <string>
#include "../location/location.h"

class Vehicle
{
private:
    std::string id;
    std::string licensePlate;
    std::string make;
    std::string model;
    std::string color;
    std::string transmissionType;
    std::string fuelType;

    int year;
    int seatingCapacity;
    bool availabilityStatus;
    double rentalRates;
    double mileage;

    std::shared_ptr<Location> location;

public:
    Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates, double mileage = 0.0);
    Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates, std::shared_ptr<Location> location, double mileage = 0.0);
    ~Vehicle() = default;

    std::string getId() const;
    std::string getLicensePlate() const;
    std::string getMake() const;
    std::string getModel() const;
    std::string getColor() const;
    std::string getTransmissionType() const;
    std::string getFuelType() const;

    int getYear() const;
    int getSeatingCapacity() const;
    bool getAvailabilityStatus() const;
    double getRentalRates() const;
    double getMileage() const;

    std::shared_ptr<Location> getLocation() const;

    void updateAvailabilityStatus(bool status);
    void updateLocation(std::shared_ptr<Location> location);
    void updateMileage(double mileage);

    friend std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle);
};
