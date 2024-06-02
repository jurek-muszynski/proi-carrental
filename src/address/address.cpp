#include "address.h"

Address::Address(const std::string &id, const std::string &street, const std::string &city, const std::string &country, const std::string &zipCode)
    : id(id), street(street), city(city), country(country), zipCode(zipCode) {}

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

std::ostream &operator<<(std::ostream &os, const Address &address)
{
    os << "Address: " << address.street << " Street " << address.city;
    return os;
}
