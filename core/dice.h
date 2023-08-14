#pragma once
#include <vector>
#include <cstdint>
#include <string>

struct Dice
{
    int8_t first, second;

    bool IsPair() const { return first == second; }
};

std::string to_string(const Dice&);

std::vector<Dice> AllDiceConfigs();