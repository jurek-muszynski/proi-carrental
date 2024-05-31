#include "vehicle.h"

// Constructor
Vehicle::Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates)
    : id(id), licensePlate(licensePlate), make(make), model(model), year(year), color(color), transmissionType(transmissionType), fuelType(fuelType), seatingCapacity(seatingCapacity), availabilityStatus(availabilityStatus), rentalRates(rentalRates)
{
    location = nullptr;
}

Vehicle::~Vehicle()
{
    location = nullptr;
}

// Getters
std::string Vehicle::getMake() const { return make; }
std::string Vehicle::getId() const { return id; }
std::string Vehicle::getLicensePlate() const { return licensePlate; }
std::string Vehicle::getModel() const { return model; }
int Vehicle::getYear() const { return year; }
std::string Vehicle::getColor() const { return color; }
std::string Vehicle::getTransmissionType() const { return transmissionType; }
std::string Vehicle::getFuelType() const { return fuelType; }
int Vehicle::getSeatingCapacity() const { return seatingCapacity; }
bool Vehicle::getAvailabilityStatus() const { return availabilityStatus; }
double Vehicle::getRentalRates() const { return rentalRates; }
Location *Vehicle::getLocation() const { return location; }
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
void Vehicle::updateAvailabilityStatus(bool status)
{
    this->availabilityStatus = status;
}

void Vehicle::updateLocation(Location *newLocation)
{
    if (newLocation == nullptr)
    {
        this->location = newLocation;
        setAvailabilityStatus(false);
    }
    this->location = newLocation;
}

std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle)
{
    // print id
    os << "Id: " << vehicle.id << std::endl;
    os << "License Plate: " << vehicle.licensePlate << std::endl;
    os << "Make: " << vehicle.make << std::endl;
    os << "Model: " << vehicle.model << std::endl;
    os << "Year: " << vehicle.year << std::endl;
    os << "Color: " << vehicle.color << std::endl;
    os << "Transmission Type: " << vehicle.transmissionType << std::endl;
    os << "Fuel Type: " << vehicle.fuelType << std::endl;
    os << "Seating Capacity: " << vehicle.seatingCapacity << std::endl;
    os << "Availability Status: " << (vehicle.availabilityStatus ? "Available" : "Not Available") << std::endl;
    os << "Rental Rates: " << vehicle.rentalRates << std::endl;
    if (vehicle.location)
    {
        os << "Location: \n"
           << *vehicle.location << std::endl;
    }
    else
    {
        os << "Location: Not Available" << std::endl;
    }
    return os;
}
