#include "simulation.h"

Simulation::Simulation(unsigned int sims, const std::string &filepath) : simulations_run(sims)
{
    srand(time(0));
    customerManagement = new CustomerManagement();
    fleetManagement = new FleetManagement();
    rentalManagement = new RentalManagement();
    current_time = std::chrono::system_clock::now();
    loadData(filepath);
}

Simulation::Simulation(unsigned int sims, CustomerManagement *cm, FleetManagement *fm, RentalManagement *rm) : simulations_run(sims), customerManagement(cm), fleetManagement(fm), rentalManagement(rm)
{
    current_time = std::chrono::system_clock::now();
}

void Simulation::passTime()
{
    current_time += std::chrono::minutes(30);
}

std::string Simulation::getDateTime() const

{
    std::time_t tt = std::chrono::system_clock::to_time_t(current_time);
    return ctime(&tt);
}

void Simulation::run()
{
    for (unsigned int i = 0; i < simulations_run; i++)
    {
        std::cout << getDateTime() << std::endl;
        newCustomerRegistered();
        newCustomerRegistered();
        printLogs();
        passTime();
    }
}

void Simulation::loadData(const std::string &filePath)
{
    loadAddresses(filePath + "/addresses.json");
    loadCustomers(filePath + "/customers.json");
    // loadVehicles(filePath + "/vehicles.json");
}

void Simulation::loadCustomers(const std::string &filePath)
{
    std::ifstream file(filePath);

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

void Simulation::loadAddresses(const std::string &filePath)
{
    std::ifstream file(filePath);

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
        ss << "Indistinct id: " << newCustomer->getId() << "\n";
    }
    logs.push_back(ss.str());
}

void Simulation::printLogs()
{
    for (int i = 0; i < logs.size(); i++)
    {
        std::cout << i + 1 << ". " << logs[i];
    }
    logs.clear();
}
