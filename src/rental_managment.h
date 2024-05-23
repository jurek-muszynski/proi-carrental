#include "rental.h"
#include <string>
#include <vector>

class RentalManagement {
public:
    void createRental(Customer* customer, Vehicle* vehicle, int duration);
    void closeRental(std::string id);
    Rental* getRental(std::string id);
private:
    std::vector<Rental*> rentals;
};