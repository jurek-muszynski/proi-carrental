#include "rental.h"

Rental::Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration)
    : id(id), customer(customer), vehicle(vehicle), duration(duration)
{
    if (!vehicle->getAvailabilityStatus())
    {
        throw std::invalid_argument("Vehicle is not available, please choose another vehicle.");
    }
}

Rental::~Rental()
{
    customer = nullptr;
    vehicle = nullptr;
}

double Rental::calculateCost() const
{
    return duration * vehicle->getRentalRates();
}

std::string Rental::getId() const
{
    return id;
}

Customer *Rental::getCustomer() const
{
    return customer;
}

Vehicle *Rental::getVehicle() const
{
    return vehicle;
}

int Rental::getDuration() const
{
    return duration;
}