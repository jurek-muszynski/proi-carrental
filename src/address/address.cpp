#include "address.h"

Address::Address(const std::string &id, const std::string &street, const std::string &city, const std::string &country, const std::string &zipCode, double longitude, double latitude)
    : id(id), street(street), city(city), country(country), zipCode(zipCode), longitude(longitude), latitude(latitude) 
    {
        if (longitude < -180.0 || longitude > 180.0) {
            throw std::invalid_argument("Invalid longitude");
        }
        if (latitude < -90.0 || latitude > 90.0) {
            throw std::invalid_argument("Invalid latitude");
        }
    }

std::string Address::getId() const
{
    return this->id;
}

std::string Address::getStreet() const
{
    return this->street;
}

std::string Address::getCity() const
{
    return this->city;
}

std::string Address::getCountry() const
{
    return this->country;
}

std::string Address::getZipCode() const
{
    return this->zipCode;
}

double Address::getLongitude() const
{
    return this->longitude;
}

double Address::getLatitude() const
{
    return this->latitude;
}

std::ostream &operator<<(std::ostream &os, const Address &address)
{
    os << "Address: " << address.getStreet() << " Street " << address.getCity();
    return os;
}
