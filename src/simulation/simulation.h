#pragma once

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>
#include <time.h>
#include <unistd.h>
#include "../customer/customer_management.h"
#include "../fleet/fleet_management.h"
#include "../rental/rental_management.h"
#include "simulation_report.h"

using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

class Simulation
{
private:
    std::chrono::system_clock::time_point current_time;
    unsigned int simulations_run = 0;

    std::string dataPath;

    CustomerManagement *customerManagement;
    FleetManagement *fleetManagement;
    RentalManagement *rentalManagement;

    std::vector<Customer *> loadedCustomers;
    std::vector<Vehicle *> loadedVehicles;
    std::vector<Address *> loadedAddresses;
    std::vector<Location *> loadedLocations;

    std::vector<std::pair<Vehicle *, std::chrono::system_clock::time_point>> vehiclesUnderMaintenance;

    std::vector<std::string> logs;

    SimulationReport report;

public:
    Simulation(unsigned int sims, const std::string &filePath);
    Simulation(unsigned int sims, CustomerManagement *cm, FleetManagement *fm, RentalManagement *rm, const std::string &filePath);

    std::string getDateTime() const;

    void passTime();
    void run();

    void loadData();
    void loadCustomers();
    void loadVehicles();
    void loadAddresses();
    void loadLocations();

    Customer *chooseRandomCustomer(std::vector<Customer *> customers) const;
    Customer *chooseRandomCustomerToRegister(std::vector<Customer *> customers) const;
    Customer *chooseRandomCustomerToRent(std::vector<Customer *> customers) const;

    Location *chooseRandomDropOffLocation(std::vector<Location *> locations, Location *currentLocation) const;

    Vehicle *chooseRandomVehicleForMaintenance() const;
    Vehicle *chooseRandomVehicleUnderMaintenance(std::vector<std::pair<Vehicle *, std::chrono::system_clock::time_point>> vehicles) const;

    std::vector<Vehicle *> getVehiclesUnderMaintenance() const;

    void newCustomerRegistered();
    void newRentalOpened();
    void newRentalClosed();
    void scheduleVehicleMaintenance();
    void finishVehicleMaintenance();

    void printLogs();
};
