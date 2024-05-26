#pragma once

#include "../vehicle/vehicle.h"
#include "../customer/customer.h"
#include <string>

class Rental
{
public:
    Rental(std::string id, Customer *customer, Vehicle *vehicle, int duration);
    double calculateCost();
    std::string getId();
    Customer *getCustomer();
    Vehicle *getVehicle();
    int getDuration();

private:
    std::string id;
    Customer *customer;
    Vehicle *vehicle;
    int duration;
    static double rate;
};
