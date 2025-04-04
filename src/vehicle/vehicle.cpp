#include "vehicle.h"

Vehicle::Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year,
                 std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity,
                 bool availabilityStatus, double rentalRates, double mileage)
    : id(id), licensePlate(licensePlate), make(make), model(model), year(year), color(color), transmissionType(transmissionType),
      fuelType(fuelType), seatingCapacity(seatingCapacity), availabilityStatus(availabilityStatus), rentalRates(rentalRates), mileage(mileage)
{
    location = nullptr;
}

Vehicle::Vehicle(std::string id, std::string licensePlate, std::string make, std::string model, int year,
                 std::string color, std::string transmissionType, std::string fuelType, int seatingCapacity,
                 bool availabilityStatus, double rentalRates, std::shared_ptr<Location> location, double mileage)
    : id(id), licensePlate(licensePlate), make(make), model(model), year(year), color(color), transmissionType(transmissionType),
      fuelType(fuelType), seatingCapacity(seatingCapacity), availabilityStatus(availabilityStatus), rentalRates(rentalRates),
      location(std::move(location)), mileage(mileage)
{
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

double Vehicle::getMileage() const
{
    return mileage;
}

bool Vehicle::getAvailabilityStatus() const
{
    return availabilityStatus;
}

std::shared_ptr<Location> Vehicle::getLocation() const
{
    return location;
}

void Vehicle::updateAvailabilityStatus(bool status)
{
    availabilityStatus = status;
}

void Vehicle::updateLocation(std::shared_ptr<Location> newLocation)
{
    if (newLocation == nullptr)
    {
        location = nullptr;
        updateAvailabilityStatus(false);
    }
    this->location = std::move(newLocation);
}

void Vehicle::updateMileage(double distance)
{
    mileage += distance;
}

std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle)
{
    os << "Vehicle: " << vehicle.make << " License Plate: " << vehicle.licensePlate << " Rental Rates: " << vehicle.rentalRates << "$";
    if (vehicle.location)
    {
        os << "\n\t" << *vehicle.location;
    }
    else
    {
        os << " Location: Not Available";
    }
    return os;
}
