#pragma once

#include <string>
#include "../address/address.h"
class Location
{
private:
    int locationId;
    std::string name;
    Address *address;

public:
    Location(int id, std::string locName, Address *address)
        : locationId(id), name(locName), address(address)
    {
    }

    // Getters
    int getLocationId() const;
    std::string getName() const;
    Address *getAddress() const;
};
