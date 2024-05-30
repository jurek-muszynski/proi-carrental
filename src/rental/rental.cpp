#include "rental.h"

Rental::Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration)
    : id(id), customer(customer), vehicle(vehicle), duration(duration) {}

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
    delete customer;
    customer = nullptr;
    delete vehicle;
    vehicle = nullptr;
}
