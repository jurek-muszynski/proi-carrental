#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <memory>
#include "../address/address.h"

class Location
{
private:
    int locationId;
    std::string name;
    std::shared_ptr<Address> address;

public:
    Location(int id, std::string name, std::shared_ptr<Address> address);
    ~Location() = default;

    int getLocationId() const;
    std::string getName() const;
    std::shared_ptr<Address> getAddress() const;

    double calculateDistance(const Location &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Location &location);
};
