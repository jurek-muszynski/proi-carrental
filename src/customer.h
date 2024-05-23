#include <string>

class Customer {
public:
    Customer(std::string id, std::string name, std::string contact);
    void updateContact(std::string contact);
    std::string getId();
    std::string getName();
    std::string getContact();
private:
    std::string id;
    std::string name;
    std::string contact;
};