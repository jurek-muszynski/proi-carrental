#include "rental.h"

Rental::Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration)
    : id(id), customer(customer), vehicle(vehicle), duration(duration)
{
    // check happens if the vehicle is unavailable?
    if (!vehicle->getAvailabilityStatus())
    {
        throw std::invalid_argument("Vehicle is not available, please choose another vehicle.");
    }
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
    return this->customer;
}

Vehicle *Rental::getVehicle() const
{
    return this->vehicle;
}

int Rental::getDuration() const
{
    return this->duration;
}

Rental::~Rental()
{
    customer = nullptr;
    vehicle = nullptr;
}
