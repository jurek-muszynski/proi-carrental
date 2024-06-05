#include <iostream>
// #include <fstream>
// #include <iostream>
// #include <algorithm>
// #include <string>

// #include "src/fleet/fleet_management.h"
// #include "src/customer/customer_management.h"
// #include "src/rental/rental_management.h"
// #include "src/simulation/simulation.h"

#include "src/userInterface/userInterface.h"


// // int main()
// // {
// //     // SAMPLE DEMO -> pass the absolute path to the data folder in case it throws a json file error

// //     // RentalManagement *rm = new RentalManagement();
// //     // CustomerManagement *cm = new CustomerManagement();
// //     // FleetManagement *fm = new FleetManagement();

// //     // Simulation sim(10, cm, fm, rm, "/home/mlewko/proi/24l-proi-lewko-muszynski/data");
// //     // sim.run();
// //     // return 0;

    
// // }

int main() {
    std::string id = "C001";
    std::string firstName = "John";
    std::string lastName = "Doe";
    std::tm birthDate = {};
    birthDate.tm_year = 2003 - 1900; // years since 1900
    birthDate.tm_mon = 2 - 1;       // months since January (0-11)
    birthDate.tm_mday = 1;      
    std::string gender = "Male";
    std::string email = "john.doe@example.com";
    std::string phoneNumber = "123456789";
    Address* address = new Address("Street", "City", "State", "Country", "ZipCode");

    std::string dataPath = "/home/mlewko/proi/24l-proi-lewko-muszynski/data";
    Customer* customer = new Customer(id, firstName, lastName, birthDate, gender, email, phoneNumber, address);

    UserInterface ui(dataPath, customer);

    // Wyświetl menu i obsłuż wybór użytkownika
    int choice;
    do {
        ui.displayMenu();
        std::cin >> choice;
        ui.handleUserChoice(choice);
    } while (choice != 0);  // Zakładam, że 0 to wybór wyjścia z programu


    return 0;
}


