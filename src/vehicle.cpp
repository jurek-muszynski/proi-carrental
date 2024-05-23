#include "vehicle.h"

Vehicle::Vehicle(std::string id, std::string make, std::string model, std::string status) 
    : id(id), make(make), model(model), status(status) {}

void Vehicle::updateStatus(std::string status) {
    this->status = status;
}

std::string Vehicle::getId() {
    return this->id;
}

std::string Vehicle::getMake()
{
    return this->make;
}

std::string Vehicle::getModel() {
    return this->model;
}

std::string Vehicle::getStatus() {
    return this->status;
}