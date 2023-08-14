#pragma once
#include <cstdint>
#include <string>
#include <vector>

constexpr int8_t off = 0;
constexpr int8_t bar = 25;

struct Move
{
    int8_t from{0}, to{0};
    Move(int from, int to) noexcept : from(static_cast<int8_t>(from)), to(static_cast<int8_t>(to)) {}
    auto operator<=>(const Move&) const = default;
};

using Moves = std::vector<Move>;

std::string to_string(const Move&);
std::string to_string(const Moves&);
