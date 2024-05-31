#pragma once

#include <nlohmann/json.hpp>
using ordered_json = nlohmann::ordered_json;
using namespace nlohmann;

#include "../vehicle/vehicle.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class FleetManagement
{
private:
    std::vector<Vehicle *> vehicles;

public:
    // Constructor
    FleetManagement(std::vector<Vehicle *> vehicles = {});
    // Constructor with path to JSON file
    FleetManagement(const std::string &filePath);

    void addVehicle(Vehicle *vehicle);
    void removeVehicle(const std::string id);
    Vehicle *getVehicle(const std::string id) const;
    // overload the getVehicle() method based on the transmissionType

    std::vector<Vehicle *> getAvailableVehicles();

    // Function to load vehicles from JSON file
    void loadVehiclesFromJson(const std::string &filePath);

    // Overloaded << operator to output all vehicles
    friend std::ostream &operator<<(std::ostream &os, const FleetManagement &fleet);

    // Destructor
    ~FleetManagement();
};
