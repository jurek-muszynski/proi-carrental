#include <stdexcept>
#include "userInterface.h"


class NotImplementedError : public std::logic_error
{
public:
    NotImplementedError() : std::logic_error("Function not yet implemented") { };
};

UserInterface::UserInterface(const std::string& dataPath, Customer* customer) : dataPath(dataPath), customer(customer), fleetManagement(fleetManagement), rentalManagement(rentalManagement) {

    srand(time(0));
    fleetManagement = new FleetManagement();
    rentalManagement = new RentalManagement();
    current_time = std::chrono::system_clock::now();
    loadData();
}

UserInterface::~UserInterface()
{
}

void UserInterface::displayMenu() {
    std::cout << "1. Wypożycz samochód\n";
    std::cout << "2. Oddaj samochód\n";
    std::cout << "Wybierz opcję: ";
}

void UserInterface::handleUserChoice(int choice) {
    switch (choice) {
        case 1:
            rentCarOption();
            break;
        case 2:
            returnCarOption();
            break;
        default:
            std::cout << "Nieznana opcja\n";
            break;
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

void UserInterface::printLocations() const
{
    for (const auto& location : loadedLocations) {
    const Address* address = location->getAddress();
    std::cout << "ID: " << address->getId() << ", "
                << "ZIP Code: " << address->getZipCode() << ", "
                << "Street: " << address->getStreet() << ", "
                << "City: " << address->getCity() << "\n";
    }
}

void UserInterface::printVehicles(int seatingCapacity) const {

    auto availableVehicles = fleetManagement->getAvailableVehicles();

    for (const auto& vehicle : availableVehicles) {
        if (vehicle->getSeatingCapacity() == seatingCapacity) {
            std::cout << "ID: " << vehicle->getId() << " "
                      << "Make: " << vehicle->getMake() << " "
                      << "Model: " << vehicle->getModel() << " "
                      << "Color: " << vehicle->getColor() << " "
                      << "Transmission type: " << vehicle->getTransmissionType() << " "
                      << "Fuel type: " << vehicle->getFuelType() << " "
                      << "Year of production: " << vehicle->getYear() << " "
                      << "Rental rates: " << vehicle->getRentalRates() << "\n";
        }
    }
}

void UserInterface::rentCarOption()
{
    std::cout << "1. Choose a location\n";
    printLocations();

    std::string locationId;
    std::cout << "Enter location ID: ";
    std::cin >> locationId;

    Location* selectedLocation = nullptr;
    for (const auto& location : loadedLocations) {
        if (location->getAddress()->getId() == locationId) {
            selectedLocation = location;
            break;
        }
    }
    if (selectedLocation == nullptr) {
        std::cout << "No location found with the provided ID.\n";
        return;
    }

    std::cout << "2. Choose a drop-off location\n";
    printLocations();

    std::string dropOffLocationId;
    std::cout << "Enter drop-off location ID: ";
    std::cin >> dropOffLocationId;

    Location* selectedDropOffLocation = nullptr;
    for (const auto& location : loadedLocations) {
        if (location->getAddress()->getId() == dropOffLocationId) {
            selectedDropOffLocation = location;
            break;
        }
    }
    if (selectedDropOffLocation == nullptr) {
        std::cout << "No location found with the provided ID.\n";
        return;
    }

    std::cout << "3. Choose rental duration\n";
    int duration;
    std::cout << "Enter rental duration (in days): ";
    std::cin >> duration;

    std::cout << "4. Choose vehicle seating capacity\n";
    int seatingCapacity;
    std::cout << "Enter seating capacity: ";
    std::cin >> seatingCapacity;

    std::cout << "5. Choose a vehicle\n";
    printVehicles(seatingCapacity);

    // TODO: jakoś inaczej wybierać samochody

    std::string vehicleId;
    std::cout << "Enter vehicle ID: ";
    std::cin >> vehicleId;

    Vehicle* selectedVehicle = nullptr;
    for (const auto& vehicle : loadedVehicles) {
        if (vehicle->getId() == vehicleId && vehicle->getSeatingCapacity() == seatingCapacity) {
            selectedVehicle = vehicle;
            break;
        }
    }
    if (selectedVehicle == nullptr) {
        std::cout << "No available vehicle found with the provided ID and seating capacity.\n";
        return;
    }

    const std::string rentalId = "R" + customer->getId() + "/" + selectedVehicle->getLicensePlate();
    Rental* newRental = new Rental(rentalId, customer, selectedVehicle, duration);

    newRental->setDropOffLocation(selectedDropOffLocation);

    double cost = newRental->calculateCost();
    std::cout << "The cost of the rental will be: " << cost << " $\n";

    auto returnTime = newRental->getRentTime() + std::chrono::hours(24 * duration);
    std::time_t returnTime_t = std::chrono::system_clock::to_time_t(returnTime);
    std::cout << "The rental will end on: " << std::ctime(&returnTime_t) << std::endl;

    rentalManagement->openRental(newRental);
}

void UserInterface::returnCarOption()
{
    throw NotImplementedError();
}

Location UserInterface::readLocation()
{
    throw NotImplementedError();
}

int UserInterface::readDuration()
{
    throw NotImplementedError();
}

int UserInterface::readSeatingCapacity()
{
    throw NotImplementedError();
}

Vehicle UserInterface::readVehicle()
{
    throw NotImplementedError();
}


Rental UserInterface::rentCar(Customer &customer, Vehicle &vehicle, Location &location, int duration)
{
    // const std::string rentalId = "R" + customer->getId() + "/" + vehicle->getLicensePlate();
    // const Rental *newRental = new Rental(rentalId, customer, vehicle, duration);
    // return *newRental;
    throw NotImplementedError();
}

Rental UserInterface::returnCar()
{
    throw NotImplementedError();
}


