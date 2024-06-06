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
    return_time = rent_time + std::chrono::hours(duration);
}

Rental::~Rental()
{
    customer = nullptr;
    vehicle = nullptr;
    pickupLocation = nullptr;
    dropOffLocation = nullptr;
}

double Rental::calculateCost() const
{
    return duration * vehicle->getRentalRates();
}

double Rental::calculateDistance() const
{
    double distance = pickupLocation->calculateDistance(*dropOffLocation);

    if (pickupLocation != nullptr && dropOffLocation != nullptr)
        if (distance > 1000)
            return distance / 100;
        else
            return distance;

    return 0.0;
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
    vehicle->updateMileage(calculateDistance());
}

int Rental::getDuration() const
{
    return duration;
}

std::ostream &operator<<(std::ostream &os, const Rental &rental)
{
    os << "Total Cost: " << rental.calculateCost() << " $";
    os << "\n\tDuration: " << rental.getDuration() << " hours";
    os << "\n\tDistance: " << std::fixed << std::setprecision(2) << rental.calculateDistance() << " km";
    return os;
}
