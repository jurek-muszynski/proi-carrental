#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include "../address/address.h"

class Location
{
private:
    int locationId;
    std::string name;
    Address *address;

public:
    Location(int id, std::string name, Address *address);
    ~Location();

    int getLocationId() const;
    std::string getName() const;
    Address *getAddress() const;

    double calculateDistance(const Location &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Location &location);
};
