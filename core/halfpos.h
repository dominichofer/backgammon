#pragma once
#include "dice.h"
#include "move.h"
#include <array>
#include <cstdint>
#include <string>

class HalfPos
{
    std::array<int8_t, 25> fields;
public:
    HalfPos() noexcept = default;
    explicit HalfPos(std::array<int8_t, 25> fields) noexcept : fields(std::move(fields)) {}

    auto operator<=>(const HalfPos&) const = default;

    int Checkers() const;
    int8_t Checkers(int index) const { return fields[index - 1]; }
    int8_t& Checkers(int index) { return fields[index - 1]; }
    int Pips() const;
    int HighestChecker() const;
    bool CanBearOff() const;
    bool IsGameOver() const;

    Moves PossibleMoves(int pips) const;
    std::vector<Moves> PossibleMoves(const Dice&) const;

    void Play(const Move&);
};

std::string to_string(const HalfPos&);

HalfPos Play(HalfPos, const Moves&);

template <>
struct std::hash<HalfPos>
{
    std::size_t operator()(const HalfPos&) const;
};
