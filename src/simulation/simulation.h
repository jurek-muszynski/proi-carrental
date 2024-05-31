#include <chrono>
#include <ctime>

class Simulation
{
private:
    std::chrono::system_clock::time_point current_time;

public:
    Simulation()
    {
        current_time = std::chrono::system_clock::now();
    }
    void run();
    void passTime()
    {
        current_time += std::chrono::minutes(30);
    }

    std::string getDateTime()
    {
        std::time_t tt = std::chrono::system_clock::to_time_t(current_time);
        return ctime(&tt);
    }
};
