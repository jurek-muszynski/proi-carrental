#pragma once

#include <string>
#include <sstream>
#include <iomanip>

class ReportEntity
{
protected:
    int rentalCount = 0;
    double totalCost = 0;

public:
    virtual ~ReportEntity() = default;
    void addCost(double amount);
    void addRentalCount();
    virtual std::string generateReport() const = 0;
};

class CustomerData : public ReportEntity
{
private:
    double totalDuration = 0;

public:
    void addDuration(double duration);

    std::string generateReport() const override;
};

class VehicleData : public ReportEntity
{
private:
    int maintenanceCount = 0;
    int mileage = 0;

public:
    void addMaintenanceCount();

    std::string generateReport() const override;
};