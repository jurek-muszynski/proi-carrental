#include "vehicle.h"

// Constructor
Vehicle::Vehicle(std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates)
    : make(make), model(model), year(year), color(color), transmissionType(transmissionType), fuelType(fuelType), seatingCapacity(seatingCapacity), availabilityStatus(availabilityStatus), rentalRates(rentalRates) {}

// Getters
std::string Vehicle::getMake() { return make; }
std::string Vehicle::getModel() { return model; }
int Vehicle::getYear() { return year; }
std::string Vehicle::getColor() { return color; }
std::string Vehicle::getTransmissionType() { return transmissionType; }
std::string Vehicle::getFuelType() { return fuelType; }
int Vehicle::getSeatingCapacity() { return seatingCapacity; }
bool Vehicle::getAvailabilityStatus() { return availabilityStatus; }
double Vehicle::getRentalRates() { return rentalRates; }

// Setters
void Vehicle::setMake(std::string make) { this->make = make; }
void Vehicle::setModel(std::string model) { this->model = model; }
void Vehicle::setYear(int year) { this->year = year; }
void Vehicle::setColor(std::string color) { this->color = color; }
void Vehicle::setTransmissionType(std::string transmissionType) { this->transmissionType = transmissionType; }
void Vehicle::setFuelType(std::string fuelType) { this->fuelType = fuelType; }
void Vehicle::setSeatingCapacity(int seatingCapacity) { this->seatingCapacity = seatingCapacity; }
void Vehicle::setAvailabilityStatus(bool availabilityStatus) { this->availabilityStatus = availabilityStatus; }
void Vehicle::setRentalRates(double rentalRates) { this->rentalRates = rentalRates; }

// Method to update availability status
void Vehicle::updateAvailabilityStatus(bool status) {
    this->availabilityStatus = status;
}