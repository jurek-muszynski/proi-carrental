
#pragma once
#include "../vehicle/vehicle.h"

class Truck : public Vehicle
{
private:
    double cargoCapacity;

public:
    Truck(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates, double cargoCapacity, double mileage = 0.0)
        : Vehicle(id, licensePlate, make, model, year, color, transmissionType, fuelType, seatingCapacity, availabilityStatus, rentalRates, mileage), cargoCapacity(cargoCapacity) {}

    double getCargoCapacity() const { return cargoCapacity; }
};