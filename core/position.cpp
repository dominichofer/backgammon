#include "position.h"
#include "algorithm.h"
#include <algorithm>
#include <cmath>
#include <format>
#include <numeric>

Position Position::Start() noexcept
{
    return Position{ std::array<int8_t, 26>{ 0,-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2,0 } };
}

[[nodiscard]] HalfPos Position::Player() const
{
    std::array<int8_t, 25> pos;
    for (int i = 0; i < pos.size(); i++)
        pos[i] = std::max<int8_t>(0, fields[i + 1]);
    return HalfPos{ pos };
}

HalfPos Position::Opponent() const
{
    std::array<int8_t, 25> pos;
    for (int i = 0; i < pos.size(); i++)
        pos[i] = std::max<int8_t>(0, -fields[24 - i]);
    return HalfPos{ pos };
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
        c(13, 1), c(14, 1), c(15, 1), c(16, 1), c(17, 1), c(18, 1), c(off, 1), c(19, 1), c(20, 1), c(21, 1), c(22, 1), c(23, 1), c(24, 1),
        c(13, 2), c(14, 2), c(15, 2), c(16, 2), c(17, 2), c(18, 2), c(off, 2), c(19, 2), c(20, 2), c(21, 2), c(22, 2), c(23, 2), c(24, 2),
        c(13, 3), c(14, 3), c(15, 3), c(16, 3), c(17, 3), c(18, 3), c(off, 3), c(19, 3), c(20, 3), c(21, 3), c(22, 3), c(23, 3), c(24, 3),
        c(13, 4), c(14, 4), c(15, 4), c(16, 4), c(17, 4), c(18, 4), c(off, 4), c(19, 4), c(20, 4), c(21, 4), c(22, 4), c(23, 4), c(24, 4),
        c(13, 5), c(14, 5), c(15, 5), c(16, 5), c(17, 5), c(18, 5), c(off, 5), c(19, 5), c(20, 5), c(21, 5), c(22, 5), c(23, 5), c(24, 5),
        c(12, 5), c(11, 5), c(10, 5), c(9, 5), c(8, 5), c(7, 5), c(bar, 1), c(6, 5), c(5, 5), c(4, 5), c(3, 5), c(2, 5), c(1, 5),
        c(12, 4), c(11, 4), c(10, 4), c(9, 4), c(8, 4), c(7, 4), c(bar, 2), c(6, 4), c(5, 4), c(4, 4), c(3, 4), c(2, 4), c(1, 4),
        c(12, 3), c(11, 3), c(10, 3), c(9, 3), c(8, 3), c(7, 3), c(bar, 3), c(6, 3), c(5, 3), c(4, 3), c(3, 3), c(2, 3), c(1, 3),
        c(12, 2), c(11, 2), c(10, 2), c(9, 2), c(8, 2), c(7, 2), c(bar, 4), c(6, 2), c(5, 2), c(4, 2), c(3, 2), c(2, 2), c(1, 2),
        c(12, 1), c(11, 1), c(10, 1), c(9, 1), c(8, 1), c(7, 1), c(bar, 5), c(6, 1), c(5, 1), c(4, 1), c(3, 1), c(2, 1), c(1, 1)
    );
}

bool Position::CanBearOff() const
{
    return std::all_of(fields.begin() + 7, fields.end(), [](int8_t v) { return v <= 0; });
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

Moves Position::PossibleMoves(int pips) const
{
    Moves moves;

    if (Checkers(bar) > 0 && !IsBlocked(bar - pips))
        return Moves{ {bar, bar - pips} };

    // On board
    for (int i = pips + 1; i < bar; i++)
        if (Checkers(i) > 0 && !IsBlocked(i - pips))
            moves.emplace_back(i, i - pips);

    if (CanBearOff())
    {
        if (Checkers(pips) > 0)
            moves.emplace_back(pips, off);
        else if (moves.empty())
            for (int i = pips - 1; i > 0; i--)
                if (Checkers(i) > 0)
                    return Moves{ {i, off} };
    }

    return moves;
}

std::vector<Moves> Position::PossibleMoves(const Dice& dice) const
{
    std::vector<Moves> moves;
    if (dice.IsPair())
    {
        int8_t d = dice.first;
        for (const Move& m1 : PossibleMoves(d))
        {
            Position next_1 = *this;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                moves.push_back({ m1 });
            else
                for (const Move& m2 : next_1.PossibleMoves(d))
                {
                    Position next_2 = next_1;
                    next_2.Play(m2);
                    if (next_2.IsGameOver())
                        moves.push_back({ m1, m2 });
                    else
                        for (const Move& m3 : next_2.PossibleMoves(d))
                        {
                            Position next_3 = next_2;
                            next_3.Play(m3);
                            if (next_3.IsGameOver())
                                moves.push_back({ m1, m2, m3 });
                            else
                                for (const Move& m4 : next_3.PossibleMoves(d))
                                    moves.push_back({ m1, m2, m3, m4 });
                        }
                }
        }
    }
    else
    {
        for (const Move& m1 : PossibleMoves(dice.first))
        {
            Position next_1 = *this;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                moves.push_back({ m1 });
            else
                for (const Move& m2 : next_1.PossibleMoves(dice.second))
                    moves.push_back({ m1, m2 });
        }
        for (const Move& m1 : PossibleMoves(dice.second))
        {
            Position next_1 = *this;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                moves.push_back({ m1 });
            else
                for (const Move& m2 : next_1.PossibleMoves(dice.first))
                    moves.push_back({ m1, m2 });
        }
    }
    return moves;
}

void Position::Play(const Move& move)
{
    fields[move.from]--;
    if (move.to == off)
        return;
    if (fields[move.to] < 0) // hit
    {
        fields.front() += fields[move.to];
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

std::size_t std::hash<Position>::operator()(const Position& pos) const
{
    uint64_t sum = 0;
    for (int i = 0; i < 16; i++)
        sum += static_cast<uint64_t>(pos.Checkers(i)) << (4 * i);
    return std::hash<uint64_t>()(sum);
}
