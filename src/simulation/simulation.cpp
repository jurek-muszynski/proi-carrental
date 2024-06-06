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
    std::cout << "Simulation has just started\n";
    usleep(2000000);
    logs.push_back(getDateTime() + "\n");

    std::default_random_engine generator(time(0));
    std::poisson_distribution<int> newCustomerDistribution(1);
    std::poisson_distribution<int> newRentalDistribution(2);

    for (unsigned int i = 0; i < simulations_run; i++)
    {
        int newCustomers = newCustomerDistribution(generator);
        int newRentals = newRentalDistribution(generator);

        for (int j = 0; j < newCustomers; j++)
        {
            if (generateRandomly(0.88))
                newCustomerRegistered();
        }

        for (int j = 0; j < newRentals; j++)
        {
            if (customerManagement->getCustomerCount() > 0)
            {
                if (generateRandomly(0.65))
                    newRentalOpened();
            }
            else
                break;
        }

        while (rentalManagement->getRentalsToBeTerminated(current_time).size() > 0)
        {
            newRentalClosed();
        }

        if (fleetManagement->getVehicleCount() > 0 && generateRandomly(0.35))
            scheduleVehicleMaintenance();

        if (vehiclesUnderMaintenance.size() > 0 && generateRandomly(0.4))
            finishVehicleMaintenance();

        if (fleetManagement->getVehicleCount() > 0 && customerManagement->getCustomerCount() > 0 && generateRandomly(0.15))
            reportAccident();

        if (customerManagement->getCustomerCount() > 0 && generateRandomly(0.22))
            updateCustomerData();

        printLogs();
        passTime();
        usleep(2000000);
    }

    std::cout << "\nSimulation has ended after " << simulations_run << " iterations\n";
    report.generateCustomerSummary();
    report.generateVehicleSummary();
}

void Simulation::loadData()
{
    loadAddresses();
    loadCustomers();
    loadAdmins();
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
        double latitude = address["latitude"];
        double longitude = address["longitude"];

        Address *newAddress = new Address(id, street, city, country, zip, longitude, latitude);
        loadedAddresses.push_back(newAddress);
    }
}

void Simulation::loadAdmins()
{
    std::ifstream file(dataPath + "/admins.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open json file");

    json source = json::parse(file);

    for (const auto &admin : source)
    {
        std::tm birthDate = {};
        birthDate.tm_year = 2000 - 1900; // years since 1900
        birthDate.tm_mon = 12 - 1;       // months since January (0-11)
        birthDate.tm_mday = 1;           // day of the month (1-31)
        std::string id = admin["id"];
        std::string first_name = admin["fname"];
        std::string last_name = admin["lname"];
        std::string email = admin["email"];
        std::string phone = admin["phoneNumber"];
        std::string gender = admin["gender"];

        Address *address = loadedAddresses[rand() % loadedAddresses.size()];
        AdminUser *newAdmin = new AdminUser(id, first_name, last_name, birthDate, gender, email, phone, address);
        fleetManagement->addAdmin(newAdmin);
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

AdminUser *Simulation::chooseRandomAdminForMaintenance(std::vector<AdminUser *> admins) const
{
    if (admins.empty())
        throw std::runtime_error("No admins to choose from");
    return admins[rand() % admins.size()];
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

Customer *Simulation::chooseRandomCustomerNotRenting(std::vector<Customer *> customers) const
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
        return nullptr;

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

Vehicle *Simulation::chooseRandomVehicleForMaintenance() const
{
    std::vector<Vehicle *> availableVehiclesForMaintenance = fleetManagement->getAvailableVehicles();

    if (availableVehiclesForMaintenance.empty())
        throw std::runtime_error("No vehicles to choose from");

    return availableVehiclesForMaintenance[rand() % availableVehiclesForMaintenance.size()];
}

std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>> Simulation::chooseRandomVehicleUnderMaintenance(std::vector<std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>>> vehicles) const
{
    if (vehicles.empty())
        throw std::runtime_error("No vehicles to choose from");

    std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>> randomVehicleUnderMaintenancePair = vehicles[rand() % vehicles.size()];
    while (current_time == randomVehicleUnderMaintenancePair.second.second)
        randomVehicleUnderMaintenancePair = vehicles[rand() % vehicles.size()];
    return randomVehicleUnderMaintenancePair;
}

Vehicle *Simulation::chooseRandomVehicleForAccident(std::vector<Vehicle *> vehicles) const
{
    if (vehicles.empty())
        return nullptr;

    return vehicles[rand() % vehicles.size()];
}

std::vector<Vehicle *> Simulation::getVehiclesUnderMaintenance() const
{
    std::vector<Vehicle *> vehiclesUnderMaintenance;
    std::vector<Vehicle *> unavailableVehicles = fleetManagement->getUnavailableVehicles();

    for (auto &vehicle : unavailableVehicles)
    {
        if (!rentalManagement->isVehicleCurrentlyRented(vehicle))
        {
            vehiclesUnderMaintenance.push_back(vehicle);
        }
    }

    return vehiclesUnderMaintenance;
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
    Customer *customer = chooseRandomCustomerNotRenting(customerManagement->getCustomers());

    if (customer == nullptr)
        return;

    std::vector<Vehicle *> availableVehicles = fleetManagement->getAvailableVehicles();
    Vehicle *vehicle = availableVehicles[rand() % availableVehicles.size()];
    Location *dropOff = loadedLocations[rand() % loadedLocations.size()];

    const std::string rentalId = "R" + customer->getId() + "/" + vehicle->getLicensePlate();
    int duration = rand() % 10 + 1;
    Rental *newRental = new Rental(rentalId, customer, vehicle, duration, current_time);
    newRental->setDropOffLocation(chooseRandomDropOffLocation(loadedLocations, newRental->getVehicle()->getLocation()));
    std::stringstream ss;
    if (rentalManagement->openRental(newRental))
    {
        ss << "New rental opened: " << *customer << " rented\n\t" << *vehicle << "\n\tDuration: " << duration << " hours\n";
        logs.push_back(ss.str());
        report.addRentalData(newRental);
    }
}

void Simulation::newRentalClosed(Rental *rentalToBeTerminated)
{
    Rental *rental = rentalToBeTerminated;

    if (rentalToBeTerminated == nullptr)
        rental = rentalManagement->getRentalsToBeTerminated(current_time)[0];

    std::stringstream ss;
    if (rentalManagement->closeRental(rental->getId()))
    {
        if (rentalToBeTerminated == nullptr)
            ss << "Rental closed: " << *rental->getCustomer() << " returned\n\t" << *rental->getVehicle() << "\n\t" << *rental << "\n";
        else
            ss << "Rental terminated after an accident: " << *rental->getCustomer() << "\n";

        logs.push_back(ss.str());
    }
}

void Simulation::scheduleVehicleMaintenance(Vehicle *vehicleToMaintain)
{
    Vehicle *vehicle = vehicleToMaintain;
    if (vehicleToMaintain == nullptr)
        vehicle = chooseRandomVehicleForMaintenance();

    AdminUser *admin = chooseRandomAdminForMaintenance(fleetManagement->getAdmins());
    admin->performVehicleMaintenance(vehicle);

    vehiclesUnderMaintenance.push_back(std::make_pair(vehicle, std::make_pair(admin, current_time)));

    std::stringstream ss;
    if (vehicleToMaintain == nullptr)
        ss << "Scheduled maintenance for " << *vehicle << "\n";
    else
        ss << "Maintenance after an accident " << *vehicle << "\n";
    ss << "\tTo be repaired by Admin: " << *admin << "\n";
    logs.push_back(ss.str());
    report.addMaintenanceData(vehicle);
}

void Simulation::updateCustomerData()
{
    Customer *customer = chooseRandomCustomerNotRenting(customerManagement->getCustomers());

    if (customer == nullptr)
        return;

    std::string oldEmail = customer->getEmail();

    std::stringstream ss;
    customer->updateEmail(generateRandomlyEmail(customer->getFirstName(), customer->getLastName()));
    ss << "Updated data for: " << *customer << "\n";
    ss << "\tOld email: " << oldEmail << "\n";
    ss << "\tNew email: " << customer->getEmail() << "\n";
    logs.push_back(ss.str());
}

void Simulation::finishVehicleMaintenance()
{
    std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>> vehicleData = chooseRandomVehicleUnderMaintenance(vehiclesUnderMaintenance);
    Vehicle *vehicle = vehicleData.first;
    AdminUser *admin = vehicleData.second.first;
    admin->finishVehicleMaintenance(vehicle);
    vehiclesUnderMaintenance.erase(std::remove_if(vehiclesUnderMaintenance.begin(), vehiclesUnderMaintenance.end(), [vehicle](const std::pair<Vehicle *, std::pair<AdminUser *, std::chrono::system_clock::time_point>> &pair)
                                                  { return pair.first == vehicle; }),
                                   vehiclesUnderMaintenance.end());
    std::stringstream ss;
    ss << "Finished maintenance for: " << *vehicle << "\n";
    ss << "\tMaintained by Admin: " << *admin << "\n";
    logs.push_back(ss.str());
}

void Simulation::reportAccident()
{
    Vehicle *vehicle = chooseRandomVehicleForAccident(rentalManagement->getCurrentVehicles());

    if (vehicle == nullptr)
        return;

    Rental *rentalToBeClosed = rentalManagement->getRentalByVehicleId(vehicle->getId());

    std::stringstream ss;
    ss << "Accident reported for: " << *vehicle << "\n";
    logs.push_back(ss.str());
    newRentalClosed(rentalToBeClosed);
    scheduleVehicleMaintenance(vehicle);
    report.addAccidentData(vehicle);
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
