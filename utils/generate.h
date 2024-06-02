#pragma once

#include <random>

bool generateRandomly(const double percentage)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen) < percentage;
}
