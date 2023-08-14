#include "dice.h"

std::string to_string(const Dice& dice)
{
    return std::to_string(dice.first) + '-' + std::to_string(dice.second);
}

std::vector<Dice> AllDiceConfigs()
{
    return {
        Dice{1,1}, Dice{1,2}, Dice{1,3}, Dice{1,4}, Dice{1,5}, Dice{1,6},
        Dice{2,2}, Dice{2,3}, Dice{2,4}, Dice{2,5}, Dice{2,6},
        Dice{3,3}, Dice{3,4}, Dice{3,5}, Dice{3,6},
        Dice{4,4}, Dice{4,5}, Dice{4,6},
        Dice{5,5}, Dice{5,6},
        Dice{6,6}
    };
}
