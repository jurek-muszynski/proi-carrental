#include <iostream>
#include "src/userInterface/userInterface.h"

void handleException(const std::string &message)
{
    std::cout << message;
}

int main()
{
    // Tworzenie przykładowego customera
    std::string id = "C001";
    std::string firstName = "John";
    std::string lastName = "Doe";
    std::tm birthDate = {};
    birthDate.tm_year = 2003 - 1900;
    birthDate.tm_mon = 2 - 1;
    birthDate.tm_mday = 1;
    std::string gender = "Male";
    std::string email = "john.doe@example.com";
    std::string phoneNumber = "123456789";
    Address *address = new Address("Street", "City", "State", "Country", "ZipCode");
    Customer *customer = new Customer(id, firstName, lastName, birthDate, gender, email, phoneNumber, address);

    // Ścieżka do pliku
    std::string dataPath = "data";

    // Stworzenie interfejsu dla użytkownika
    UserInterface ui(dataPath, customer);

    // Wyświetlenie menu i obsłużenie wyboru użytkownika, wraz z wyjątkami
    std::string input;
    int choice;
    do
    {
        ui.displayMenu();
        std::cin >> input;
        try
        {
            choice = std::stoi(input);
            ui.handleUserChoice(choice);
        }
        catch (std::invalid_argument &)
        {
            handleException("Invalid choice. Please enter a number '1' or '2'.\n");
            continue;
        }
        catch (std::out_of_range &)
        {
            handleException("Invalid choice. Please enter a number '1' or '2'.\n");
            continue;
        }
    } while (choice != 2); // Zakładam, że 0 to wybór wyjścia z programu

    return 0;
}
