#include <nlohmann/json.hpp>
#include "../fleet/fleet_management.h"
#include "../vehicle/vehicle.h"
#include "../rental/rental.h"
#include "../location/location.h"
#include "../customer/customer.h"
#include "../rental/rental_management.h"

using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

class UserInterface
{
public:
    UserInterface(const std::string& dataPath, Customer* customer);

    ~UserInterface();

    void displayMenu();

    void handleUserChoice(int choice);

    void loadVehicles();
    void loadLocations();
    void loadAddresses();

    void loadData();

    void printLocations() const;
    void printVehicles(int seatingCapacity) const;

private:
    std::chrono::system_clock::time_point current_time;
    std::string dataPath;
    Customer *customer;
    FleetManagement *fleetManagement;
    RentalManagement *rentalManagement;
    
    std::vector<Address *> loadedAddresses;
    std::vector<Location *> loadedLocations;
    std::vector<Vehicle *> loadedVehicles;

    void rentCarOption();
    void returnCarOption();

    Location readLocation();
    int readDuration();
    int readSeatingCapacity();
    Vehicle readVehicle();

    Rental rentCar(Customer &customer, Vehicle &car, Location &location, int duration);
    Rental returnCar();
};