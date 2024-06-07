#include <iostream>
#include <memory>

#include "src/userInterface/userInterface.h"

int main()
{
    std::string id = "C001";
    std::string firstName = "John";
    std::string lastName = "Doe";
    std::tm birthDate = {};
    birthDate.tm_year = 2003 - 1900; // years since 1900
    birthDate.tm_mon = 2 - 1;        // months since January (0-11)
    birthDate.tm_mday = 1;
    std::string gender = "Male";
    std::string email = "john.doe@example.com";
    std::string phoneNumber = "123456789";
    std::shared_ptr<Address> address = std::make_shared<Address>("Street", "City", "State", "Country", "ZipCode");

    std::string dataPath = "../data";
    std::shared_ptr<Customer> customer = std::make_shared<Customer>(id, firstName, lastName, birthDate, gender, email, phoneNumber, address);

    std::unique_ptr<UserInterface> ui = std::make_unique<UserInterface>(dataPath, customer);

    // Wyświetl menu i obsłuż wybór użytkownika
    int choice;
    do
    {
        ui->displayMenu();
        std::cin >> choice;
        ui->handleUserChoice(choice);
    } while (choice != 2); // Zakładam, że 0 to wybór wyjścia z programu

    return 0;
}
