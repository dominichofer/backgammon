#pragma once
#include "move.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string>

class HalfPos
{
    std::array<int8_t, 25> fields{0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0};
public:
    HalfPos() noexcept = default;
    HalfPos(std::array<int8_t, 25> fields) noexcept : fields(std::move(fields)) {}

    auto operator<=>(const HalfPos& o) const { return fields <=> o.fields; }

    int Checkers() const { return std::accumulate(fields.begin(), fields.end(), 0); }
    int Checkers(int index) const { return fields[index]; }
    int CheckersOnBar() const { return fields.back(); }
    int Pips() const;
    bool CanBearOff() const;
    bool IsGameOver() const;

    void Play(const Move&);
    
    std::size_t hash() const;
};

std::string to_string(const HalfPos&);


class Position
{
    std::array<int8_t, 26> fields;
public:
    Position() noexcept = default;
    Position(std::array<int8_t, 26> fields) noexcept : fields(std::move(fields)) {}

    static Position Start() noexcept;

    [[nodiscard]] HalfPos Player() const;
    [[nodiscard]] HalfPos Opponent() const;

    bool IsEndgame() const;
    bool IsGameOver() const;

    //Moves PossibleMoves(int pips) const;
    void Play(const Move&);
    void Flip();

    std::string to_string() const;
};

std::string to_string(const Position&);

Position Play(Position, const Moves&);
Position PlayPass(Position);