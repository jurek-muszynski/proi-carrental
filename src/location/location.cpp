#include "location.h"

Location::Location(int id, std::string locName, std::shared_ptr<Address> address)
    : locationId(id), name(locName), address(std::move(address))
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

std::shared_ptr<Address> Location::getAddress() const
{
    return address;
}

double Location::calculateDistance(const Location &other) const
{
    if (other.address == nullptr)
    {
        throw std::invalid_argument("The other location does not have an address.");
    }
    const double earthRadiusKm = 6371.0;

    double lat1 = address->getLatitude() * M_PI / 180.0;
    double lon1 = address->getLongitude() * M_PI / 180.0;
    double lat2 = other.address->getLatitude() * M_PI / 180.0;
    double lon2 = other.address->getLongitude() * M_PI / 180.0;

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1) * cos(lat2) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = earthRadiusKm * c;

    return distance;
}

std::ostream &operator<<(std::ostream &os, const Location &location)
{
    os << "Location ID: " << location.getLocationId()
       << " Name: " << location.getName();
    if (location.getAddress() != nullptr)
    {
        os << "\n\t" << *(location.getAddress());
    }
    return os;
}
