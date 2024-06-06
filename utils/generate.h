#pragma once

#include <random>

bool generateRandomly(const double percentage)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen) < percentage;
}

std::string generateRandomlyEmail(const std::string &firstName, const std::string &lastName)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    std::string domain = "@example.com";
    return firstName + "." + lastName + std::to_string(dis(gen)) + domain;
}