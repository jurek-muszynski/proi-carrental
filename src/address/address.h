#include <string>

class Address {
private:
    std::string id;
    std::string street;
    std::string city;
    std::string state;
    std::string zipCode;

public:
    Address(const std::string& id, const std::string& street, const std::string& city, const std::string& state, const std::string& zipCode);

    std::string getId() const;
    std::string getStreet() const;
    std::string getCity() const;
    std::string getState() const;
    std::string getZipCode() const;

    void setId(const std::string& id);
    void setStreet(const std::string& street);
    void setCity(const std::string& city);
    void setState(const std::string& state);
    void setZipCode(const std::string& zipCode);
};
