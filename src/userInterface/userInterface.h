#pragma once

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <unistd.h>
#include <memory>
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

private:
    std::chrono::system_clock::time_point current_time;
    std::string dataPath;
    std::shared_ptr<Customer> customer;
    std::unique_ptr<FleetManagement> fleetManagement;
    std::shared_ptr<Rental> rental;
    std::unique_ptr<RentalManagement> rentalManagement;

    std::vector<std::shared_ptr<Address>> loadedAddresses;
    std::vector<std::shared_ptr<Location>> loadedLocations;
    std::vector<std::shared_ptr<Vehicle>> loadedVehicles;

    void rentCarOption();
    void returnCarOption();

public:
    UserInterface(const std::string &dataPath, std::shared_ptr<Customer> customer);

    ~UserInterface() = default;

    void displayMenu();
    void handleUserChoice(int choice);

    void loadVehicles();
    void loadLocations();
    void loadAddresses();
    void loadData();

    void printLocations();
    void printVehicles(int seatingCapacity);
    void printRental();
};