#include <array>

struct Dice
{
    int first, second;

    static std::array<Dice, 21> All();

    bool IsPair() const { return first == second; }
};
