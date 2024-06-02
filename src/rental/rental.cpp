#include "rental.h"

Rental::Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration, std::chrono::system_clock::time_point rent_time)
    : id(id), customer(customer), vehicle(vehicle), duration(duration), rent_time(rent_time)
{
    if (!vehicle->getAvailabilityStatus())
    {
        throw std::invalid_argument("Vehicle is not available, please choose another vehicle.");
    }
    vehicle->updateAvailabilityStatus(false);
    pickupLocation = vehicle->getLocation();
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

std::chrono::system_clock::time_point Rental::getRentTime() const
{
    return rent_time;
}

void Rental::setDropoffLocation(Location *location)
{
    dropoffLocation = location;
    vehicle->updateLocation(location);
}

int Rental::getDuration() const
{
    return duration;
}

std::ostream &operator<<(std::ostream &os, const Rental &rental)
{
    os << "Total Cost: " << rental.calculateCost() << " $";

    return os;
}
