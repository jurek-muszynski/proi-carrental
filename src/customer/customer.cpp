#include "customer.h"
#include <memory>

Customer::Customer(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, std::shared_ptr<Address> address)
    : User(id, firstName, lastName, birthDate, gender, email, phoneNumber, address) {}
