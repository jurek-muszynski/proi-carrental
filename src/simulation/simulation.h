#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "../customer/customer_management.h"
#include "../fleet/fleet_management.h"
#include "../rental/rental_management.h"

#include <nlohmann/json.hpp>
using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

class Simulation
{
private:
    std::chrono::system_clock::time_point current_time;
    unsigned int simulations_run = 0;

    CustomerManagement *customerManagement;
    FleetManagement *fleetManagement;
    RentalManagement *rentalManagement;

    std::vector<Customer *> loadedCustomers;
    std::vector<Vehicle *> loadedVehicles;
    std::vector<Address *> loadedAddresses;

    std::vector<std::string> logs;

public:
    Simulation(unsigned int sims, const std::string &filePath);
    Simulation(unsigned int sims, CustomerManagement *cm, FleetManagement *fm, RentalManagement *rm);

    std::string getDateTime() const;

    void passTime();
    void run();

    void loadData(const std::string &filePath);
    void loadCustomers(const std::string &filePath);
    void loadVehicles(const std::string &filePath);
    void loadAddresses(const std::string &filePath);

    Customer *chooseRandomCustomer();

    void newCustomerRegistered();

    void printLogs();
};
