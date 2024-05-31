#pragma once

#include <string>

class Address
{
private:
    std::string id;
    std::string street;
    std::string city;
    std::string country;
    std::string zipCode;

public:
    Address(const std::string &id, const std::string &street, const std::string &city, const std::string &country, const std::string &zipCode);

    // Is that all necessary?
    std::string getId() const;
    std::string getStreet() const;
    std::string getCity() const;
    std::string getCountry() const;
    std::string getZipCode() const;
};
