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
    return_time = rent_time + std::chrono::hours(24 * duration);
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

std::chrono::system_clock::time_point Rental::getReturnTime() const
{
    return return_time;
}

void Rental::printReturnTime() const
{
    std::time_t returnTime_t = std::chrono::system_clock::to_time_t(getReturnTime());
    std::cout << "The rental will end on: " << std::ctime(&returnTime_t);
}

void Rental::printRentTime() const
{
    std::time_t rentTime_t = std::chrono::system_clock::to_time_t(getRentTime());
    std::cout << "The rental started on: " << std::ctime(&rentTime_t);
}

void Rental::setDropOffLocation(Location *location)
{
    dropOffLocation = location;
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
