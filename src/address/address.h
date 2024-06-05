#pragma once

#include <iostream>
#include <string>

class Address
{
private:
    std::string id;
    std::string street;
    std::string city;
    std::string country;
    std::string zipCode;
    double longitude;
    double latitude;

public:
    Address(const std::string &id, const std::string &street, const std::string &city, const std::string &country, const std::string &zipCode, double longitude = 0.0, double latitude = 0.0);

    std::string getId() const;
    std::string getStreet() const;
    std::string getCity() const;
    std::string getCountry() const;
    std::string getZipCode() const;
    double getLongitude() const;
    double getLatitude() const;

    friend std::ostream &operator<<(std::ostream &os, const Address &address);
};
