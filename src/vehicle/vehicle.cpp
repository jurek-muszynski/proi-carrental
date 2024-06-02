#include "vehicle.h"

Vehicle::Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates)
    : id(id), licensePlate(licensePlate), make(make), model(model), year(year), color(color), transmissionType(transmissionType), fuelType(fuelType), seatingCapacity(seatingCapacity), availabilityStatus(availabilityStatus), rentalRates(rentalRates)
{
    location = nullptr;
}

Vehicle::Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year, std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity, bool availabilityStatus, double rentalRates, Location *location)
    : id(id), licensePlate(licensePlate), make(make), model(model), year(year), color(color), transmissionType(transmissionType), fuelType(fuelType), seatingCapacity(seatingCapacity), availabilityStatus(availabilityStatus), rentalRates(rentalRates), location(location)
{
}

Vehicle::~Vehicle()
{
    location = nullptr;
}

std::string Vehicle::getMake() const
{
    return make;
}

std::string Vehicle::getId() const
{
    return id;
}

std::string Vehicle::getLicensePlate() const
{
    return licensePlate;
}

std::string Vehicle::getModel() const
{
    return model;
}

std::string Vehicle::getColor() const
{
    return color;
}

std::string Vehicle::getTransmissionType() const
{
    return transmissionType;
}

std::string Vehicle::getFuelType() const
{
    return fuelType;
}

int Vehicle::getYear() const
{
    return year;
}

int Vehicle::getSeatingCapacity() const
{
    return seatingCapacity;
}

double Vehicle::getRentalRates() const
{
    return rentalRates;
}

bool Vehicle::getAvailabilityStatus() const
{
    return availabilityStatus;
}

Location *Vehicle::getLocation() const
{
    return location;
}

void Vehicle::updateAvailabilityStatus(bool status)
{
    availabilityStatus = status;
}

void Vehicle::updateLocation(Location *newLocation)
{
    if (newLocation == nullptr)
    {
        location = newLocation;
        updateAvailabilityStatus(false);
    }
    location = newLocation;
}

std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle)
{
    os << "Vehicle: " << vehicle.make << " License Plate: " << vehicle.licensePlate << " Rental Rates: " << vehicle.rentalRates;
    if (vehicle.location)
    {
        os << "\n\t"
           << *vehicle.location;
    }
    else
    {
        os << " Location: Not Available";
    }
    return os;
}
