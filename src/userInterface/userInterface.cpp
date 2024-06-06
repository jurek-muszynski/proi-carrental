#include "userInterface.h"

class NotImplementedError : public std::logic_error
{
public:
    NotImplementedError() : std::logic_error("Function not yet implemented"){};
};

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
    if (choice == 1 && (rental == nullptr or rental->getVehicle()->getAvailabilityStatus()))
    {
        rentCarOption();
    }
    else if (choice == 1 && (rental != nullptr or !rental->getVehicle()->getAvailabilityStatus()))
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

    std::string locationId;
    std::cout << "Enter location ID: ";
    std::cin >> locationId;

    int selectedLocationId = std::stoi(locationId);

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
    std::cout << "Enter rental duration (in days): ";
    std::cin >> duration;

    std::cout << "3. Choose vehicle seating capacity\n";
    int seatingCapacity;
    std::cout << "Enter seating capacity: ";
    std::cin >> seatingCapacity;

    std::cout << "4. Choose a vehicle\n";
    printVehicles(seatingCapacity);

    std::string vehicleId;
    std::cout << "Enter vehicle ID: ";
    std::cin >> vehicleId;

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

    std::string dropOffLocationId;
    std::cout << "Enter drop-off location ID: ";
    std::cin >> dropOffLocationId;

    int selectedDropOffLocationId = std::stoi(dropOffLocationId);

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