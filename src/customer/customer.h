#pragma once

#include <string>

class Customer
{
public:
    Customer(std::string id, std::string name, std::string email, std::string contact);
    void updateContact(std::string contact);
    std::string getId();
    std::string getEmail();
    std::string getName();
    std::string getContactNumber();

private:
    std::string id;
    std::string name;
    std::string email;
    std::string contactNumber;
    // password ?????????????
};