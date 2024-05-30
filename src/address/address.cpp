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

void Address::setId(const std::string &id)
{
    this->id = id;
}

void Address::setStreet(const std::string &street)
{
    this->street = street;
}

void Address::setCity(const std::string &city)
{
    this->city = city;
}

void Address::setCountry(const std::string &country)
{
    this->country = country;
}

void Address::setZipCode(const std::string &zipCode)
{
    this->zipCode = zipCode;
}