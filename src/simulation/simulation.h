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

#include "../admin/admin.h"
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

    std::vector<std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>>> vehiclesUnderMaintenance;

    std::vector<std::string> logs;

    SimulationReport report;

public:
    Simulation(unsigned int sims, const std::string &filePath);
    Simulation(unsigned int sims, CustomerManagement *cm, FleetManagement *fm, RentalManagement *rm, const std::string &filePath);

    std::string getDateTime() const;

    void passTime();
    void run();

    void loadData();
    void loadAddresses();
    void loadAdmins();
    void loadCustomers();
    void loadLocations();
    void loadVehicles();

    AdminUser *chooseRandomAdminForMaintenance(std::vector<AdminUser *> admins) const;

    Customer *chooseRandomCustomer(std::vector<Customer *> customers) const;
    Customer *chooseRandomCustomerToRegister(std::vector<Customer *> customers) const;
    Customer *chooseRandomCustomerNotRenting(std::vector<Customer *> customers) const;

    Location *chooseRandomDropOffLocation(std::vector<Location *> locations, Location *currentLocation) const;

    Vehicle *chooseRandomVehicleForMaintenance() const;
    std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>> chooseRandomVehicleUnderMaintenance(std::vector<std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>>> vehicles) const;
    Vehicle *chooseRandomVehicleForAccident(std::vector<Vehicle *> vehicles) const;

    std::vector<Vehicle *> getVehiclesUnderMaintenance() const;

    void newCustomerRegistered();
    void newRentalOpened();
    void newRentalClosed(Rental *rental = nullptr);
    void scheduleVehicleMaintenance(Vehicle *vehicle = nullptr);
    void updateCustomerData();
    void finishVehicleMaintenance();
    void reportAccident();

    void printLogs();
};
