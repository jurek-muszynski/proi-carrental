#include <chrono>

class Simulation
{
private:
    std::chrono::system_clock::time_point date_time;

public:
    Simulation()
    {
        date_time = std::chrono::system_clock::now();
    }
    void run();
    void incrementTime()
    {
        date_time += std::chrono::minutes(15);
    }

    std::chrono::system_clock::time_point getDateTime()
    {
        // output current date and time
        return date_time;
    }
};
