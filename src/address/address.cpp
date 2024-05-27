#include "address.h"

Address::Address(const std::string& id, const std::string& street, const std::string& city, const std::string& state, const std::string& zipCode)
    : id(id), street(street), city(city), state(state), zipCode(zipCode) {}

std::string Address::getId() const
{
    return this->id;
}

std::string Address::getStreet() const
{
    return this->street;
}

std::string Address::getCity() const {
    return this->city;
}

std::string Address::getState() const {
    return this->state;
}

std::string Address::getZipCode() const {
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

void Address::setCity(const std::string& city) {
    this->city = city;
}

void Address::setState(const std::string& state) {
    this->state = state;
}

void Address::setZipCode(const std::string& zipCode) {
    this->zipCode = zipCode;
}