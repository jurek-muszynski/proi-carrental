#include "rental.h"

// Inicjalizacja statycznego składnika klasy
double Rental::rate = 10.0; // Przykładowa wartość

Rental::Rental(std::string id, Customer* customer, Vehicle* vehicle, int duration) 
    : id(id), customer(customer), vehicle(vehicle), duration(duration) {}

double Rental::calculateCost() {
    return duration * rate;
}

std::string Rental::getId() {
    return this->id;
}

Customer* Rental::getCustomer() {
    return this->customer;
}

Vehicle* Rental::getVehicle() {
    return this->vehicle;
}

int Rental::getDuration() {
    return this->duration;
}