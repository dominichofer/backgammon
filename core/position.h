#pragma once
#include "dice.h"
#include "halfpos.h"
#include "move.h"
#include <array>
#include <cmath>
#include <cstdint>
#include <string>

class Position
{
    std::array<int8_t, 26> fields;
public:
    Position() noexcept = default;
    explicit Position(std::array<int8_t, 26> fields) noexcept : fields(std::move(fields)) {}

    static Position Start() noexcept;

    auto operator<=>(const Position&) const = default;

    [[nodiscard]] HalfPos Player() const;
    [[nodiscard]] HalfPos Opponent() const;

    int Checkers(int index) const { return fields[index]; }
    bool IsBlocked(int index) const { return fields[index] < -1; }
    bool CanBearOff() const;
    bool IsEndgame() const;
    bool IsGameOver() const;

    Moves PossibleMoves(int pips) const;
    std::vector<Moves> PossibleMoves(const Dice&) const;

    void Play(const Move&);
    void Flip();

    std::string to_string() const;
};

std::string to_string(const Position&);

Position Play(Position, const Moves&);
Position PlayPass(Position);

template <>
struct std::hash<Position>
{
    std::size_t operator()(const Position&) const;
};