#include "rental_management.h"

void RentalManagement::createRental(Customer *customer, Vehicle *vehicle, int duration)
{
    // Generowanie unikalnego ID dla wypożyczenia
    std::string id = customer->getId() + vehicle->getId(); // Przykładowa metoda generowania ID

    // Tworzenie nowego wypożyczenia i dodawanie go do listy
    Rental *rental = new Rental(id, customer, vehicle, duration);
    rentals.push_back(rental);
}

void RentalManagement::closeRental(std::string id)
{
    for (int i = 0; i < rentals.size(); i++)
    {
        if (rentals[i]->getId() == id)
        {
            // Usuwanie wypożyczenia
            delete rentals[i];
            rentals.erase(rentals.begin() + i);
            break;
        }
    }
}

Rental *RentalManagement::getRental(std::string id)
{
    for (Rental *rental : rentals)
    {
        if (rental->getId() == id)
        {
            return rental;
        }
    }
    return nullptr; // Zwraca nullptr, jeśli nie znaleziono wypożyczenia
}