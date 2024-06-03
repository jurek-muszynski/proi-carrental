#include "./src/fleet/fleet_management.h"
#include "./src/vehicle/vehicle.h"
#include "./src/rental/rental.h"
#include "./src/location/location.h"
#include "./src/customer/customer.h"

class UserInterface
{
public:
    UserInterface();

    ~UserInterface();

    void displayMenu();

    void handleUserChoice(int choice);

private:
    void rentCarOption();
    void returnCarOption();

    Location readLocation();
    int readDuration();
    int readSeatingCapacity();
    Vehicle readVehicle();

    Rental rentCar(Customer &customer, Vehicle &car, Location &location, int duration);
    Rental returnCar();
};