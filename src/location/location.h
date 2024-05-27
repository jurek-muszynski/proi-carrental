#include <string>

class Location {
private:
    int locationId;
    std::string name;
    std::string address;

public:
    Location(int id, std::string locName, std::string locAddress)
        : locationId(id), name(locName), address(locAddress) {}

    // Getters
    int getLocationId() const;
    std::string getName() const;
    std::string getAddress() const;
};
