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
#include <memory>

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

    std::unique_ptr<CustomerManagement> customerManagement;
    std::unique_ptr<FleetManagement> fleetManagement;
    std::unique_ptr<RentalManagement> rentalManagement;

    std::vector<std::shared_ptr<Customer>> loadedCustomers;
    std::vector<std::shared_ptr<Vehicle>> loadedVehicles;
    std::vector<std::shared_ptr<Address>> loadedAddresses;
    std::vector<std::shared_ptr<Location>> loadedLocations;

    std::vector<std::pair<std::shared_ptr<Vehicle>, std::pair<std::shared_ptr<AdminUser>, std::chrono::system_clock::time_point>>> vehiclesUnderMaintenance;

    std::vector<std::string> logs;

    SimulationReport report;

public:
    Simulation(unsigned int sims, const std::string &filePath);
    Simulation(unsigned int sims, std::unique_ptr<CustomerManagement> cm, std::unique_ptr<FleetManagement> fm, std::unique_ptr<RentalManagement> rm, const std::string &filePath);
    ~Simulation();

    std::string getDateTime() const;

    void passTime();
    void run();

    void loadData();
    void loadAddresses();
    void loadAdmins();
    void loadCustomers();
    void loadLocations();
    void loadVehicles();

    std::shared_ptr<AdminUser> chooseRandomAdminForMaintenance(std::vector<std::shared_ptr<AdminUser>> admins) const;

    std::shared_ptr<Customer> chooseRandomCustomer(std::vector<std::shared_ptr<Customer>> customers) const;
    std::shared_ptr<Customer> chooseRandomCustomerToRegister(std::vector<std::shared_ptr<Customer>> customers) const;
    std::shared_ptr<Customer> chooseRandomCustomerNotRenting(std::vector<std::shared_ptr<Customer>> customers) const;

    std::shared_ptr<Location> chooseRandomDropOffLocation(std::vector<std::shared_ptr<Location>> locations, std::shared_ptr<Location> currentLocation) const;

    std::shared_ptr<Vehicle> chooseRandomVehicleForMaintenance() const;
    std::pair<std::shared_ptr<Vehicle>, std::pair<std::shared_ptr<AdminUser>, std::chrono::system_clock::time_point>> chooseRandomVehicleUnderMaintenance(std::vector<std::pair<std::shared_ptr<Vehicle>, std::pair<std::shared_ptr<AdminUser>, std::chrono::system_clock::time_point>>> vehicles) const;
    std::shared_ptr<Vehicle> chooseRandomVehicleForAccident(std::vector<std::shared_ptr<Vehicle>> vehicles) const;

    std::vector<std::shared_ptr<Vehicle>> getVehiclesUnderMaintenance() const;

    void newCustomerRegistered();
    void newRentalOpened();
    void newRentalClosed(std::shared_ptr<Rental> rental = nullptr);
    void scheduleVehicleMaintenance(std::shared_ptr<Vehicle> vehicle = nullptr);
    void updateCustomerData();
    void finishVehicleMaintenance();
    void reportAccident();

    void printLogs();
};
