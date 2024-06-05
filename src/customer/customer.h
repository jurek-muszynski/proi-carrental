#pragma once

#include "../user/user.h"

class Customer : public User
{

public:
    Customer(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string contact, Address *address);
};
