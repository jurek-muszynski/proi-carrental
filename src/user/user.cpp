#include "user.h"

User::User(std::string id, std::string firstName, std::string lastName, std::tm birthDate, std::string gender, std::string email, std::string phoneNumber, std::shared_ptr<Address> address)
    : id(id), firstName(firstName), lastName(lastName), birthDate(birthDate), gender(gender), email(email), phoneNumber(phoneNumber), address(address) {}

User::~User()
{
    address.reset();
}

std::string User::getId() const
{
    return id;
}

std::string User::getFirstName() const
{
    return firstName;
}

std::string User::getLastName() const
{
    return lastName;
}

std::string User::getBirthDate() const
{
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &birthDate);

    return std::string(buffer);
}

std::string User::getGender() const
{
    return gender;
}

std::string User::getEmail() const
{
    return email;
}

std::string User::getPhoneNumber() const
{
    return phoneNumber;
}

std::shared_ptr<Address> User::getAddress() const
{
    return address;
}

void User::updateAddress(std::shared_ptr<Address> new_address)
{
    address = new_address;
}

void User::updatePhoneNumber(std::string new_number)
{
    phoneNumber = new_number;
}

void User::updateEmail(std::string new_email)
{
    email = new_email;
}

std::ostream &operator<<(std::ostream &os, const User &user)
{
    os << user.firstName << " " << user.lastName;
    os << " - " << user.email;

    return os;
}
