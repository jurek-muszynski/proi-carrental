#include "simulation.h"

Simulation::Simulation(unsigned int sims, const std::string &filePath) : simulations_run(sims)
{
    srand(time(0));

    customerManagement = new CustomerManagement();
    fleetManagement = new FleetManagement();
    rentalManagement = new RentalManagement();

    current_time = std::chrono::system_clock::now();
    dataPath = filePath;

    loadData();
}

Simulation::Simulation(unsigned int sims, CustomerManagement *cm, FleetManagement *fm, RentalManagement *rm, const std::string &filePath) : simulations_run(sims), customerManagement(cm), fleetManagement(fm), rentalManagement(rm)
{
    srand(time(0));

    current_time = std::chrono::system_clock::now();
    dataPath = filePath;
}

void Simulation::passTime()
{
    current_time += std::chrono::hours(2);
    logs.push_back("\n" + getDateTime() + "\n");
}

std::string Simulation::getDateTime() const

{
    std::time_t tt = std::chrono::system_clock::to_time_t(current_time);
    return ctime(&tt);
}

void Simulation::run()
{
    logs.push_back(getDateTime() + "\n");
    for (unsigned int i = 0; i < simulations_run; i++)
    {
        unsigned int newRegistrations = rand() % 3;
        for (unsigned int j = 0; j < newRegistrations; j++)
        {
            newCustomerRegistered();
        }
        printLogs();
        passTime();
        usleep(2000000);
    }
}

void Simulation::loadData()
{
    loadAddresses();
    loadCustomers();
    loadLocations();
    loadVehicles();
}

void Simulation::loadCustomers()
{
    std::ifstream file(dataPath + "/customers.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open json file");

    json source = json::parse(file);

    for (const auto &customer : source)
    {
        std::tm birthDate = {};
        birthDate.tm_year = 2000 - 1900; // years since 1900
        birthDate.tm_mon = 12 - 1;       // months since January (0-11)
        birthDate.tm_mday = 1;           // day of the month (1-31)
        std::string id = customer["id"];
        std::string first_name = customer["fname"];
        std::string last_name = customer["lname"];
        std::string email = customer["email"];
        std::string phone = customer["phoneNumber"];
        std::string gender = customer["gender"];

        Address *address = loadedAddresses[rand() % loadedAddresses.size()];
        Customer *newCustomer = new Customer(id, first_name, last_name, birthDate, gender, email, phone, address);
        loadedCustomers.push_back(newCustomer);
    }
}

void Simulation::loadAddresses()
{
    std::ifstream file(dataPath + "/addresses.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open json file");

    json source = json::parse(file);

    for (const auto &address : source)
    {
        std::string id = address["id"];
        std::string street = address["street"];
        std::string city = address["city"];
        std::string zip = address["zip_code"];
        std::string country = address["country"];

        Address *newAddress = new Address(id, street, city, country, zip);
        loadedAddresses.push_back(newAddress);
    }
}

void Simulation::loadLocations()
{
    std::ifstream file(dataPath + "/locations.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open json file");

    json source = json::parse(file);

    for (const auto &location : source)
    {
        int id = location["id"];
        std::string name = location["name"];

        Address *address = loadedAddresses[rand() % loadedAddresses.size()];
        Location *newLocation = new Location(id, name, address);
        loadedLocations.push_back(newLocation);
    }
}

void Simulation::loadVehicles()
{
    std::ifstream file(dataPath + "/vehicles.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open json file");

    json source = json::parse(file);

    for (const auto &vehicle : source)
    {
        std::string id = vehicle["id"];
        std::string make = vehicle["make"];
        std::string model = vehicle["model"];
        int year = vehicle["year"];
        std::string color = vehicle["color"];
        std::string licensePlate = vehicle["licensePlate"];
        std::string transmissionType = vehicle["transmissionType"];
        std::string fuelType = vehicle["fuelType"];
        int seatingCapacity = vehicle["seatingCapacity"];
        bool status = vehicle["availabilityStatus"];
        double rentalRates = vehicle["rentalRates"];

        Location *location = loadedLocations[rand() % loadedLocations.size()];
        Vehicle *newVehicle = new Vehicle(id, licensePlate, make, model, year, color, transmissionType, fuelType, seatingCapacity, status, rentalRates);
        loadedVehicles.push_back(newVehicle);
    }
}

Customer *Simulation::chooseRandomCustomer()
{
    if (loadedCustomers.empty())
        throw std::runtime_error("No customers loaded");
    return loadedCustomers[rand() % loadedCustomers.size()];
}

void Simulation::newCustomerRegistered()
{
    Customer *newCustomer = chooseRandomCustomer();
    std::stringstream ss;
    if (customerManagement->addCustomer(newCustomer))
    {
        ss << "New customer registered: " << *newCustomer << "\n";
    }
    else
    {
        ss << "Customer: " << *newCustomer << " has already been registered\n";
    }
    logs.push_back(ss.str());
}

void Simulation::printLogs()
{
    for (int i = 0; i < logs.size(); i++)
    {
        if (i > 0)
        {
            std::cout << i << ". ";
        }
        std::cout << logs[i];
        usleep(1000000);
    }

    logs.clear();
}
