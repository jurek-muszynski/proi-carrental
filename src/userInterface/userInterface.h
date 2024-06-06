#pragma once

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <unistd.h>
#include "../fleet/fleet_management.h"
#include "../vehicle/vehicle.h"
#include "../rental/rental.h"
#include "../location/location.h"
#include "../customer/customer.h"
#include "../rental/rental_management.h"

using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

class UserInterface
{
public:
    UserInterface(const std::string &dataPath, Customer *customer);

    ~UserInterface();

    void displayMenu();
    void handleUserChoice(int choice);

    void loadVehicles();
    void loadLocations();
    void loadAddresses();
    void loadData();

    void printLocations();
    void printVehicles(int seatingCapacity);
    void printRental();

private:
    std::chrono::system_clock::time_point current_time;
    std::string dataPath;
    Customer *customer;

    FleetManagement *fleetManagement;
    std::vector<Address *> loadedAddresses;
    std::vector<Location *> loadedLocations;

    Rental *rental;
    RentalManagement *rentalManagement;

    void rentCarOption();
    void returnCarOption();
};