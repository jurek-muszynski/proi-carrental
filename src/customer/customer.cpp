#include "customer.h"

Customer::Customer(std::string id, std::string fname, std::string lname, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, Address address) 
    : id(id), fname(fname), lname(lname), birthDate(birthDate), gender(gender), email(email), phoneNumber(phoneNumber), address(address) {}

void Customer::updatePhoneNumber(std::string new_number)
{
    phoneNumber = new_number;
}

void Customer::updateEmail(std::string new_email)
{
    email = new_email;
}

std::string Customer::getId()
{
    return this->id;
}

std::string Customer::getFname() {
    return this->fname;
}

std::string Customer::getLname() {
    return this->lname;
}

std::string Customer::getBirthDate()
{
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &this->birthDate);
    return std::string(buffer);
}

std::string Customer::getGender()
{
    return this->gender;
}

std::string Customer::getEmail()
{
    return this->email;
}

std::string Customer::getPhoneNumber()
{
    return this->phoneNumber;
}

Address Customer::getAddress()
{
    return this->address;
}

void Customer::updateAddress(Address new_address)
{
    this->address = new_address;
}