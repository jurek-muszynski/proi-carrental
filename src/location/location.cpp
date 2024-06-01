#include "location.h"

Location::Location(int id, std::string locName, Address *address) : locationId(id), name(locName), address(address)
{
}

int Location::getLocationId() const
{
    return locationId;
}

std::string Location::getName() const
{
    return name;
}

Address *Location::getAddress() const
{
    return address;
}

Location::~Location()
{
    address = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Location &location)
{
    os << location.name << "(id:" << location.locationId << ")" << std::endl;
    return os;
}
