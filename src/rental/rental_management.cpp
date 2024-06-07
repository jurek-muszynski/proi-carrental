#include "rental_management.h"
#include <algorithm>
#include <memory>

const std::shared_ptr<Rental> RentalManagement::getRental(const std::string &id) const
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        return *it;
    }
    return nullptr;
}

std::shared_ptr<Rental> RentalManagement::getRentalByVehicleId(const std::string &id) const
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> rental)
                           { return rental->getVehicle()->getId() == id; });

    if (it != rentals.end())
    {
        return *it;
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Rental>> RentalManagement::getRentals() const
{
    return rentals;
}

const std::vector<std::shared_ptr<Customer>> RentalManagement::getCurrentCustomers() const
{
    std::vector<std::shared_ptr<Customer>> customers;
    for (const auto &rental : rentals)
    {
        customers.push_back(rental->getCustomer());
    }
    return customers;
}

const std::vector<std::shared_ptr<Vehicle>> RentalManagement::getCurrentVehicles() const
{
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    for (const auto &rental : rentals)
    {
        vehicles.push_back(rental->getVehicle());
    }
    return vehicles;
}

const std::vector<std::shared_ptr<Rental>> RentalManagement::getRentalsToBeTerminated(std::chrono::system_clock::time_point current_time) const
{
    std::vector<std::shared_ptr<Rental>> rentalsToBeTerminated;

    for (const auto &rental : rentals)
    {
        if (rental->getRentTime() + std::chrono::hours(rental->getDuration()) <= current_time)
        {
            rentalsToBeTerminated.push_back(rental);
        }
    }
    return rentalsToBeTerminated;
}

bool RentalManagement::isCustomerCurrentlyRenting(const std::shared_ptr<Customer> customer) const
{

    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> rental)
                           { return rental->getCustomer()->getId() == customer->getId(); });

    return it != rentals.end();
}

bool RentalManagement::isVehicleCurrentlyRented(const std::shared_ptr<Vehicle> vehicle) const
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> rental)
                           { return rental->getVehicle()->getId() == vehicle->getId(); });

    return it != rentals.end();
}

bool RentalManagement::openRental(const std::shared_ptr<Rental> rental)
{
    if (rental == nullptr)
    {
        return false;
    }

    auto rentalIndexIterator = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> &r)
                                            { return r->getId() == rental->getId(); });

    auto customerIndexIterator = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> &r)
                                              { return r->getCustomer()->getId() == rental->getCustomer()->getId(); });

    if (rentalIndexIterator == rentals.end() && customerIndexIterator == rentals.end())
    {
        rental->getVehicle()->updateAvailabilityStatus(false);
        rentals.push_back(rental);
        return true;
    }
    return false;
}

bool RentalManagement::closeRental(const std::string &id)
{
    auto it = std::find_if(rentals.begin(), rentals.end(), [&](const std::shared_ptr<Rental> rental)
                           { return rental->getId() == id; });

    if (it != rentals.end())
    {
        (*it)->getVehicle()->updateAvailabilityStatus(true);
        rentals.erase(it);
        return true;
    }
    return false;
}
