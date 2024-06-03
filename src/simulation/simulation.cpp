#include "simulation.h"
#include "../../utils/generate.h"

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

    loadData();
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
        if (generateRandomly(0.95))
            newCustomerRegistered();

        if (customerManagement->getCustomerCount() > 0 && generateRandomly(0.55))
            newRentalOpened();

        while (rentalManagement->getRentalsToBeTerminated(current_time).size() > 0)
        {
            newRentalClosed();
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
        newVehicle->updateLocation(location);
        fleetManagement->addVehicle(newVehicle);
    }
}

Customer *Simulation::chooseRandomCustomer(std::vector<Customer *> customers) const
{
    if (customers.empty())
        throw std::runtime_error("No customers to choose from");
    return customers[rand() % customers.size()];
}

Customer *Simulation::chooseRandomCustomerToRegister(std::vector<Customer *> customers) const
{
    if (customers.empty())
        throw std::runtime_error("No customers to choose from");
    Customer *customer = customers[rand() % customers.size()];
    while (customerManagement->isCustomerAlreadyRegistered(customer))
    {
        customer = customers[rand() % customers.size()];
    }
    return customer;
}

Customer *Simulation::chooseRandomCustomerToRent(std::vector<Customer *> customers) const
{
    std::vector<Customer *> availableCustomersToRent;
    for (auto &customer : customers)
    {
        if (!rentalManagement->isCustomerCurrentlyRenting(customer))
        {
            availableCustomersToRent.push_back(customer);
        }
    }

    if (availableCustomersToRent.empty())
        throw std::runtime_error("No customers to choose from");

    return availableCustomersToRent[rand() % availableCustomersToRent.size()];
}

Location *Simulation::chooseRandomDropOffLocation(std::vector<Location *> locations, Location *currentLocation) const
{
    if (locations.empty())
        throw std::runtime_error("No locations to choose from");

    Location *location = locations[rand() % locations.size()];
    while (location == currentLocation)
    {
        location = locations[rand() % locations.size()];
    }
    return location;
}

void Simulation::newCustomerRegistered()
{
    Customer *newCustomer = chooseRandomCustomerToRegister(loadedCustomers);
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

void Simulation::newRentalOpened()
{
    Customer *customer = chooseRandomCustomerToRent(customerManagement->getCustomers());
    std::vector<Vehicle *> availableVehicles = fleetManagement->getAvailableVehicles();
    Vehicle *vehicle = availableVehicles[rand() % availableVehicles.size()];
    Location *dropOff = loadedLocations[rand() % loadedLocations.size()];

    const std::string rentalId = "R" + customer->getId() + "/" + vehicle->getLicensePlate();
    int duration = rand() % 10 + 1;
    Rental *newRental = new Rental(rentalId, customer, vehicle, duration, current_time);
    std::stringstream ss;
    if (rentalManagement->openRental(newRental))
    {
        ss << "New rental opened: " << *customer << " rented\n\t" << *vehicle << "\n\tDuration: " << duration << " hours\n";
        logs.push_back(ss.str());
    }
}

void Simulation::newRentalClosed()
{
    Rental *rental = rentalManagement->getRentalsToBeTerminated(current_time)[0];
    rental->setDropOffLocation(chooseRandomDropOffLocation(loadedLocations, rental->getVehicle()->getLocation()));
    std::stringstream ss;
    if (rentalManagement->closeRental(rental->getId()))
    {
        ss << "Rental closed: " << *rental->getCustomer() << " returned\n\t" << *rental->getVehicle() << "\n\t" << *rental << "\n";
        logs.push_back(ss.str());
    }
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
