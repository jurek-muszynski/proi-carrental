#include "customer.h"

Customer::Customer(std::string id, std::string name, std::string contact) 
    : id(id), name(name), contact(contact) {}

void Customer::updateContact(std::string contact) {
    this->contact = contact;
}

std::string Customer::getId() {
    return this->id;
}

std::string Customer::getName() {
    return this->name;
}

std::string Customer::getContact() {
    return this->contact;
}