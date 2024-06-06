#include "userInterface.h"

UserInterface::UserInterface(const std::string &dataPath, Customer *customer) : dataPath(dataPath), customer(customer), fleetManagement(fleetManagement), rentalManagement(rentalManagement)
{
    srand(time(0));
    fleetManagement = new FleetManagement();
    rentalManagement = new RentalManagement();
    current_time = std::chrono::system_clock::now();
    loadData();
}

UserInterface::~UserInterface()
{
    delete fleetManagement;
    delete rentalManagement;
}

void UserInterface::displayMenu()
{
    if (rental == nullptr or rental->getVehicle()->getAvailabilityStatus())
    {
        std::cout << "1. Rent a car\n";
        std::cout << "2. Quit\n";
        std::cout << "Choose option: ";
    }
    else
    {
        std::cout << "1. Return a car\n";
        std::cout << "2. Quit\n";
        std::cout << "Choose option: ";
    }
}

void UserInterface::handleUserChoice(int choice)
{
    if (choice == 1 && (rental == nullptr || rental->getVehicle()->getAvailabilityStatus()))
    {
        rentCarOption();
    }
    else if (choice == 1 && (rental != nullptr || !rental->getVehicle()->getAvailabilityStatus()))
    {
        returnCarOption();
    }
    else if (choice == 2)
    {
        std::cout << "Comeback later!\n";
    }
    else
    {
        std::cout << "Unknown option\n";
    }
}

void UserInterface::loadVehicles()
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

void UserInterface::loadLocations()
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

void UserInterface::loadAddresses()
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

void UserInterface::loadData()
{
    loadAddresses();
    loadLocations();
    loadVehicles();
}

void UserInterface::printLocations()
{
    for (auto location : loadedLocations)
    {
        const Address *address = location->getAddress();
        std::cout << "ID: " << location->getLocationId() << " Zone: " << location->getName() << " City: " << address->getCity() << " Street: " << address->getStreet() << "\n";
    }
}

void UserInterface::printVehicles(int seatingCapacity)
{
    auto availableVehicles = fleetManagement->getAvailableVehicles();

    for (const auto &vehicle : availableVehicles)
    {
        if (vehicle->getSeatingCapacity() == seatingCapacity)
        {
            std::cout << "ID: " << vehicle->getId() << " "
                      << "Model: " << vehicle->getModel() << " "
                      << "Transmission type: " << vehicle->getTransmissionType() << " "
                      << "Rental rates: " << vehicle->getRentalRates() << " $\n";
        }
    }
}

void UserInterface::printRental()
{
    if (rental == nullptr)
    {
        std::cout << "No current rental.\n";
        return;
    }
    usleep(1000000);
    std::cout << "\n";
    std::cout << "Rental ID: " << rental->getId() << "\n";
    std::cout << "Vehicle: " << rental->getVehicle()->getMake() << " " << rental->getVehicle()->getModel() << "\n";
    std::cout << "Customer: " << rental->getCustomer()->getFirstName() << " " << rental->getCustomer()->getLastName() << "\n";
    rental->printRentTime();
    rental->printReturnTime();
    std::cout << "---------------------------------\n";
}

void UserInterface::rentCarOption()
{
    std::cout << "1. Choose a location\n";
    usleep(500000);
    printLocations();
    usleep(500000);

    std::string locationIdTest;
    int selectedLocationId;
    while (true)
    {
        std::cout << "Enter location ID: ";
        std::cin >> locationIdTest;
        try
        {
            selectedLocationId = std::stoi(locationIdTest);
            break;
        }
        catch (std::invalid_argument &)
        {
            std::cout << "Invalid location ID. Please enter a number.\n";
        }
    }

    std::cout << selectedLocationId << "\n";

    Location *selectedLocation = nullptr;
    for (const auto &location : loadedLocations)
    {
        if (location->getLocationId() == selectedLocationId)
        {
            selectedLocation = location;
            break;
        }
    }
    if (selectedLocation == nullptr)
    {
        std::cout << "No location found with the provided ID.\n";
        return;
    }

    usleep(1000000);
    std::cout << "2. Choose rental duration\n";
    int duration;
    while (true)
    {
        std::cout << "Enter rental duration in hours (1-24): ";
        std::cin >> duration;
        if (std::cin.fail() || duration < 1 || duration > 24)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 24.\n";
        }
        else
        {
            break;
        }
    }

    usleep(1000000);
    std::cout << "3. Choose vehicle seating capacity (2-5)\n";
    int seatingCapacity;
    while (true)
    {
        std::cout << "Enter seating capacity: ";
        std::cin >> seatingCapacity;
        if (std::cin.fail() || seatingCapacity < 2 || seatingCapacity > 5)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 2 and 5.\n";
        }
        else
        {
            break;
        }
    }

    std::cout << "4. Choose a vehicle\n";
    usleep(500000);
    printVehicles(seatingCapacity);
    usleep(500000);

    std::string vehicleId;
    while (true)
    {
        std::cout << "Enter vehicle ID: ";
        std::cin >> vehicleId;

        if (std::all_of(vehicleId.begin(), vehicleId.end(), ::isdigit))
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Vehicle ID should be numeric.\n";
        }
    }

    Vehicle *selectedVehicle = nullptr;
    for (const auto &vehicle : fleetManagement->getAvailableVehicles())
    {
        if (vehicle->getId() == vehicleId && vehicle->getSeatingCapacity() == seatingCapacity)
        {
            selectedVehicle = vehicle;
            break;
        }
    }
    if (selectedVehicle == nullptr)
    {
        std::cout << "No available vehicle found with the provided ID and seating capacity.\n";
        return;
    }

    std::cout << "5. Choose a drop-off location\n";
    printLocations();

    std::string dropOffLocationIdTest;
    int selectedDropOffLocationId;
    while (true)
    {
        std::cout << "Enter drop-off location ID: ";
        std::cin >> dropOffLocationIdTest;
        try
        {
            selectedDropOffLocationId = std::stoi(dropOffLocationIdTest);
            break;
        }
        catch (std::invalid_argument &)
        {
            std::cout << "Invalid drop-off location ID. Please enter a number.\n";
        }
    }

    Location *selectedDropOffLocation = nullptr;
    for (const auto &location : loadedLocations)
    {
        if (location->getLocationId() == selectedDropOffLocationId)
        {
            selectedDropOffLocation = location;
            break;
        }
    }
    if (selectedDropOffLocation == nullptr)
    {
        std::cout << "No location found with the provided ID.\n";
        return;
    }

    usleep(1000000);

    const std::string rentalId = "R" + customer->getId() + "/" + selectedVehicle->getLicensePlate();
    this->rental = new Rental(rentalId, customer, selectedVehicle, duration);

    double cost = rental->calculateCost();
    std::cout << "\nThe cost of the rental will be: " << cost << " $\n";

    rental->printReturnTime();

    std::cout << "The rental will be terminated within the " << selectedDropOffLocation->getName() << " zone\n\n";

    rental->setDropOffLocation(selectedDropOffLocation);

    rentalManagement->openRental(rental);

    usleep(2000000);
}

void UserInterface::returnCarOption()
{
    if (rental == nullptr)
    {
        std::cout << "You don't have open rental\n";
        return;
    }
    else
    {
        printRental();
        std::string closeRental;
        while (true)
        {
            std::cout << "If you want to close your rental type 'yes', if not type 'no': ";
            std::cin >> closeRental;
            if (closeRental == "yes")
            {
                rentalManagement->closeRental(rental->getId());
                std::cout << "The rental has been successfully returned.\n";
                break;
            }
            else if (closeRental == "no")
            {
                break;
            }
            else
            {
                std::cout << "Try again. Write 'yes' or 'no'.\n";
            }
        }
    }
}