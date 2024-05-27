#include "customer.h"

Customer::Customer(std::string id, std::string name, std::string email, std::string contactNumber) 
    : id(id), name(name), email(email), contactNumber(contactNumber) {}

void Customer::updateContact(std::string contactNumber) {
    this->contactNumber = contactNumber;
}

std::string Customer::getId() {
    return this->id;
}

std::string Customer::getEmail()
{
    return this->email;
}

std::string Customer::getName() {
    return this->name;
}

std::string Customer::getContactNumber() {
    return this->contactNumber;
}