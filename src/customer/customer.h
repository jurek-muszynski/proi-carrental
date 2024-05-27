#pragma once

#include <string>
#include <ctime>
#include "../address/address.h"

class Customer
{
public:
    Customer(std::string id, std::string fname, std::string lname, std::tm birthDate, std::string gender, std::string email, std::string contact, Address address);
    void updatePhoneNumber(std::string new_number);
    void updateEmail(std::string new_email);
    std::string getId();
    std::string getFname();
    std::string getLname();
    std::string getBirthDate();
    std::string getGender();
    std::string getEmail();
    std::string getPhoneNumber();
    Address getAddress();
    void updateAddress(Address new_address);

private:
    std::string id;
    std::string fname;
    std::string lname;
    std::tm birthDate;
    std::string gender;
    std::string email;
    std::string phoneNumber;
    Address address;
    // password ?????????????
};

// Tworzenie daty urodzenia:
// std::tm birthDate = {};
// birthDate.tm_year = year-1900; // years since 1900
// birthDate.tm_mon = month-1; // months since January (0-11)
// birthDate.tm_mday = day; // day of the month (1-31)