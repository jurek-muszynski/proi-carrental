#pragma once

#include <string>

class Vehicle
{
private:
    std::string make;
    std::string model;
    int year;
    std::string color;
    std::string transmissionType;
    std::string fuelType;
    int seatingCapacity;
    bool availabilityStatus;
    double rentalRates;
    std::string status;
    std::string id;

public:
    // Constructor
    Vehicle(std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates);

    // Getters
    std::string getId();
    std::string getMake();
    std::string getModel();
    int getYear();
    std::string getColor();
    std::string getTransmissionType();
    std::string getFuelType();
    int getSeatingCapacity();
    bool getAvailabilityStatus();
    double getRentalRates();

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
};
