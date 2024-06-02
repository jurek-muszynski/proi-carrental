#include "customer.h"

Customer::Customer(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, Address *address)
    : id(id), firstName(firstName), lastName(lastName), birthDate(birthDate), gender(gender), email(email), phoneNumber(phoneNumber), address(address) {}

Customer::~Customer()
{
    address = nullptr;
}

std::string Customer::getId() const
{
    return id;
}

std::string Customer::getFirstName() const
{
    return firstName;
}

std::string Customer::getLastName() const
{
    return lastName;
}

std::string Customer::getBirthDate() const
{
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &birthDate);

    return std::string(buffer);
}

std::string Customer::getGender() const
{
    return gender;
}

std::string Customer::getEmail() const
{
    return email;
}

std::string Customer::getPhoneNumber() const
{
    return phoneNumber;
}

Address *Customer::getAddress() const
{
    return address;
}

void Customer::updateAddress(Address *new_address)
{
    address = new_address;
}

void Customer::updatePhoneNumber(std::string new_number)
{
    phoneNumber = new_number;
}

void Customer::updateEmail(std::string new_email)
{
    email = new_email;
}

std::ostream &operator<<(std::ostream &os, const Customer &customer)
{
    os << customer.firstName << " " << customer.lastName;
    os << " - " << customer.email;

    return os;
}
