#include "position.h"
#include "algorithm.h"
#include <cmath>
#include <format>

int HalfPos::Pips() const
{
    int sum = 0;
    for (int i = 0; i < fields.size(); i++)
        sum += fields[i] * (i + 1);
    return sum;
}

auto is_zero = [](int8_t v){ return v == 0; };

bool HalfPos::CanBearOff() const
{
    return std::all_of(fields.begin() + 6, fields.end(), is_zero);
}

bool HalfPos::IsGameOver() const
{
    return std::all_of(fields.begin(), fields.end(), is_zero);
}

void HalfPos::Play(const Move& move)
{
    fields[move.from]--;
    fields[move.to]++;
}

std::size_t HalfPos::hash() const
{
    return std::hash<uint64_t>()(
        static_cast<uint64_t>(fields[0]) + (static_cast<uint64_t>(fields[1]) << 4) +
        (static_cast<uint64_t>(fields[2]) << 8) + (static_cast<uint64_t>(fields[3]) << 12) +
        (static_cast<uint64_t>(fields[4]) << 16) + (static_cast<uint64_t>(fields[5]) << 20) +
        (static_cast<uint64_t>(fields[6]) << 24) + (static_cast<uint64_t>(fields[7]) << 28) +
        (static_cast<uint64_t>(fields[8]) << 32) + (static_cast<uint64_t>(fields[9]) << 36) +
        (static_cast<uint64_t>(fields[10]) << 40) + (static_cast<uint64_t>(fields[11]) << 44) +
        (static_cast<uint64_t>(fields[12]) << 48) + (static_cast<uint64_t>(fields[13]) << 52) +
        (static_cast<uint64_t>(fields[14]) << 56) + (static_cast<uint64_t>(fields.back()) << 60));
}

std::string to_string(const HalfPos& pos)
{
    std::string str;
    for (int i = 0; i < 25; i++)
        str += std::to_string(pos.Checkers(i)) + ' ';
    str += "bar: " + std::to_string(pos.CheckersOnBar());
    return str;
}

Position Position::Start() noexcept
{
    return Position{ std::array<int8_t, 26>{ 0,-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2,0 } };
}

[[nodiscard]] HalfPos Position::Player() const
{
    std::array<int8_t, 25> p;
    for (int i = 0; i < p.size(); i++)
        p[i] = std::max<int8_t>(0, fields[i + 1]);
    return { p };
}

[[nodiscard]] HalfPos Position::Opponent() const
{
    std::array<int8_t, 25> o;
    for (int i = 0; i < o.size(); i++)
        o[i] = std::max<int8_t>(0, -fields[25 - i]);
    return { o };
}


std::string Position::to_string() const
{
    auto c = [&](int index, int limit) -> std::string
    {
        if (limit == 5 && std::abs(fields[index]) > 5)
            return std::format("{:>2}", std::abs(fields[index]));
        if (fields[index] >= limit)
            return " X";
        if (fields[index] <= -limit)
            return " O";
        return "  ";
    };

    return std::format(
        "-------------------------------------------\n"
        "|13 14 15 16 17 18 |   |19 20 21 22 23 24 |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|                  |   |                  |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|{} {} {} {} {} {} |{} |{} {} {} {} {} {} |\n"
        "|12 11 10  9  8  7 |   | 6  5  4  3  2  1 |\n"
        "-------------------------------------------\n",
        c(13, 1), c(14, 1), c(15, 1), c(16, 1), c(17, 1), c(18, 1), c(0, 1), c(19, 1), c(20, 1), c(21, 1), c(22, 1), c(23, 1), c(24, 1),
        c(13, 2), c(14, 2), c(15, 2), c(16, 2), c(17, 2), c(18, 2), c(0, 2), c(19, 2), c(20, 2), c(21, 2), c(22, 2), c(23, 2), c(24, 2),
        c(13, 3), c(14, 3), c(15, 3), c(16, 3), c(17, 3), c(18, 3), c(0, 3), c(19, 3), c(20, 3), c(21, 3), c(22, 3), c(23, 3), c(24, 3),
        c(13, 4), c(14, 4), c(15, 4), c(16, 4), c(17, 4), c(18, 4), c(0, 4), c(19, 4), c(20, 4), c(21, 4), c(22, 4), c(23, 4), c(24, 4),
        c(13, 5), c(14, 5), c(15, 5), c(16, 5), c(17, 5), c(18, 5), c(0, 5), c(19, 5), c(20, 5), c(21, 5), c(22, 5), c(23, 5), c(24, 5),
        c(12, 5), c(11, 5), c(10, 5), c(9, 5), c(8, 5), c(7, 5), c(25, 1), c(6, 5), c(5, 5), c(4, 5), c(3, 5), c(2, 5), c(1, 5),
        c(12, 4), c(11, 4), c(10, 4), c(9, 4), c(8, 4), c(7, 4), c(25, 2), c(6, 4), c(5, 4), c(4, 4), c(3, 4), c(2, 4), c(1, 4),
        c(12, 3), c(11, 3), c(10, 3), c(9, 3), c(8, 3), c(7, 3), c(25, 3), c(6, 3), c(5, 3), c(4, 3), c(3, 3), c(2, 3), c(1, 3),
        c(12, 2), c(11, 2), c(10, 2), c(9, 2), c(8, 2), c(7, 2), c(25, 4), c(6, 2), c(5, 2), c(4, 2), c(3, 2), c(2, 2), c(1, 2),
        c(12, 1), c(11, 1), c(10, 1), c(9, 1), c(8, 1), c(7, 1), c(25, 5), c(6, 1), c(5, 1), c(4, 1), c(3, 1), c(2, 1), c(1, 1)
    );
}

bool Position::IsEndgame() const
{
    int i = 0;
    for (; i < fields.size(); i++)
        if (fields[i] < 0)
            break;
    for (; i < fields.size(); i++)
        if (fields[i] > 0)
            return false;
    return true;
}

bool Position::IsGameOver() const
{
    bool all_positive = true;
    bool all_negative = true;
    for (int8_t f : fields)
    {
        if (f < 0)
            all_positive = false;
        if (f > 0)
            all_negative = false;
    }
    return all_positive || all_negative;
}

void Position::Play(const Move& move)
{
    fields[move.from]--;
    if (move.to == 0)
        return;
    if (fields[move.to] < 0)
    {
        fields.back() += fields[move.to];
        fields[move.to] = 1;
    }
    else
        fields[move.to] += 1;
}

void Position::Flip()
{
    const std::size_t size = fields.size();
    for (int i = 0; i < size / 2; i++)
    {
        int8_t tmp = fields[i];
        fields[i] = -fields[size - 1 - i];
        fields[size - 1 - i] = -tmp;
    }
}

std::string to_string(const Position& pos)
{
    return pos.to_string();
}

Position Play(Position pos, const Moves& moves)
{
    for (const Move& move : moves)
        pos.Play(move);
    pos.Flip();
    return pos;
}

Position PlayPass(Position pos)
{
    pos.Flip();
    return pos;
}