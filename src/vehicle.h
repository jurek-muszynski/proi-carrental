#include <string>

class Vehicle {
public:
    Vehicle(std::string id, std::string make, std::string model, std::string status);
    void updateStatus(std::string status);
    std::string getId();
    std::string getMake();
    std::string getModel();
    std::string getStatus();
private:
    std::string id;
    std::string make;
    std::string model;
    std::string status;
};






