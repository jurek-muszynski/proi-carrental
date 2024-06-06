#pragma once

#include "../vehicle/vehicle.h"

class Car : public Vehicle
{
private:
    bool isConvertible;

public:
    Car(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates, bool isConvertible, double mileage = 0.0)
        : Vehicle(id, licensePlate, make, model, year, color, transmissionType, fuelType, seatingCapacity, availabilityStatus, rentalRates, mileage), isConvertible(isConvertible)
};