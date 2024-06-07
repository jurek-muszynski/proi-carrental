#pragma once

#include <ctime>
#include <memory>
#include <string>
#include "../address/address.h"

class User
{
protected:
    std::string id;
    std::string firstName;
    std::string lastName;
    std::tm birthDate;
    std::string gender;
    std::string email;
    std::string phoneNumber;
    std::shared_ptr<Address> address;

public:
    User(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string contact, std::shared_ptr<Address> address);
    ~User();

    std::string getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getBirthDate() const;
    std::string getGender() const;
    std::string getEmail() const;
    std::string getPhoneNumber() const;
    std::shared_ptr<Address> getAddress() const;

    void updateEmail(std::string new_email);
    void updatePhoneNumber(std::string new_number);
    void updateAddress(std::shared_ptr<Address> new_address);

    friend std::ostream &operator<<(std::ostream &os, const User &user);
};