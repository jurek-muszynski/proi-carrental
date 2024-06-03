#include "userInterface.h"
#include <stdexcept>

class NotImplementedError : public std::logic_error
{
public:
    NotImplementedError() : std::logic_error("Function not yet implemented") { };
};

UserInterface::UserInterface()
{
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

void UserInterface::rentCarOption()
{
    std::cout << "1. Wybierz lokalizację\n";
    // wyświetlanie wszystkich lokalizacji
    std::cout << "2. Wybierz czas wypożyczenia\n";
    // wczytywanie czasu wypożyczenia
    std::cout << "3. Wybierz ilu osobowy samochód\n";
    // wczytywanie ilości osób
    std::cout << "4. Wybierz samochód\n";
    // wczytanie samochodu
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