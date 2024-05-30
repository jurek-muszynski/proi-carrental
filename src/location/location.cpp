#include "location.h"

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