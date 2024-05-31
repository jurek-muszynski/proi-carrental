#pragma once

#include <string>
#include <ctime>
#include "../address/address.h"

class Customer
{
private:
    std::string id;
    std::string firstName;
    std::string lastName;
    std::tm birthDate;
    std::string gender;
    std::string email;
    std::string phoneNumber;
    Address *address;
    // password ?????????????
public:
    Customer(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string contact, Address *address);
    void updatePhoneNumber(std::string new_number);
    void updateEmail(std::string new_email);
    std::string getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getBirthDate() const;
    std::string getGender() const;
    std::string getEmail() const;
    std::string getPhoneNumber() const;
    Address *getAddress() const;
    void updateAddress(Address *new_address);
    ~Customer();
};

// Tworzenie daty urodzenia:
// std::tm birthDate = {};
// birthDate.tm_year = year-1900; // years since 1900
// birthDate.tm_mon = month-1; // months since January (0-11)
// birthDate.tm_mday = day; // day of the month (1-31)