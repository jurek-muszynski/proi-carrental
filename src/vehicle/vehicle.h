#pragma once

#include <string>
#include <iostream>

class Vehicle
{
private:
    std::string id;
    std::string licensePlate;
    std::string make;
    std::string model;
    int year;
    std::string color;
    std::string transmissionType;
    std::string fuelType;
    int seatingCapacity;
    bool availabilityStatus;
    double rentalRates;

public:
    // Constructor
    Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates);
    // Destructor
    ~Vehicle() = default;
    // Getters
    std::string getId() const;
    std::string getLicensePlate() const;
    std::string getMake() const;
    std::string getModel() const;
    int getYear() const;
    std::string getColor() const;
    std::string getTransmissionType() const;
    std::string getFuelType() const;
    int getSeatingCapacity() const;
    bool getAvailabilityStatus() const;
    double getRentalRates() const;

    // Setters
    void setMake(std::string make);
    void setModel(std::string model);
    void setYear(int year);
    void setColor(std::string color);
    void setTransmissionType(std::string transmissionType);
    void setFuelType(std::string fuelType);
    void setSeatingCapacity(int seatingCapacity);
    void setAvailabilityStatus(bool availabilityStatus);
    void setRentalRates(double rentalRates);

    // Method to update availability status
    void updateAvailabilityStatus(bool status);

    // Overloaded << operator to output vehicle details
    friend std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle);
};
