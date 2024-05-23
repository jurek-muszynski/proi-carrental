#include "fleet_managment.h"

void FleetManagement::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

void FleetManagement::removeVehicle(std::string id) {
    for (int i = 0; i < vehicles.size(); i++) {
        if (vehicles[i]->getId() == id) {
            delete vehicles[i];
            vehicles.erase(vehicles.begin() + i);
            break;
        }
    }
}

Vehicle* FleetManagement::getVehicle(std::string id) {
    for (Vehicle* vehicle : vehicles) {
        if (vehicle->getId() == id) {
            return vehicle;
        }
    }
    return nullptr; // Zwraca nullptr, jeśli nie znaleziono pojazdu
}

std::vector<Vehicle*> FleetManagement::getAvailableVehicles() {
    std::vector<Vehicle*> availableVehicles;
    for (Vehicle* vehicle : vehicles) {
        if (vehicle->getStatus() == "available") {
            availableVehicles.push_back(vehicle);
        }
    }
    return availableVehicles;
}