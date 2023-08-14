#include "halfpos.h"
#include "halfpos.h"
#include <algorithm>
#include <numeric>

int HalfPos::Checkers() const
{
    return std::accumulate(fields.begin(), fields.end(), 0);
}

int HalfPos::Pips() const
{
    int sum = 0;
    for (int i = 0; i < fields.size(); i++)
        sum += fields[i] * (i + 1);
    return sum;
}

int HalfPos::HighestChecker() const
{
    for (int i = bar; i > off; i--)
        if (Checkers(i))
            return i;
    return 0;
}

auto is_zero = [](int8_t v) { return v == 0; };

bool HalfPos::CanBearOff() const
{
    return std::all_of(fields.begin() + 6, fields.end(), is_zero);
}

bool HalfPos::IsGameOver() const
{
    return std::all_of(fields.begin(), fields.end(), is_zero);
}

Moves HalfPos::PossibleMoves(int pips) const
{
    Moves moves;

    if (Checkers(bar))
        return Moves{ {bar, bar - pips} };

    // On board
    for (int i = pips + 1; i < bar; i++)
        if (Checkers(i))
            moves.emplace_back(i, i - pips);

    if (CanBearOff())
    {
        if (Checkers(pips))
            moves.emplace_back(pips, off);
        else if (moves.empty())
            for (int i = pips - 1; i > 0; i--)
                if (Checkers(i))
                    return Moves{ {i, off} };
    }

    return moves;
}

std::vector<Moves> HalfPos::PossibleMoves(const Dice& dice) const
{
    std::vector<Moves> moves;
    if (dice.IsPair())
    {
        int8_t d = dice.first;
        for (const Move& m1 : PossibleMoves(d))
        {
            HalfPos next_1 = *this;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                moves.push_back({ m1 });
            else
                for (const Move& m2 : next_1.PossibleMoves(d))
                {
                    HalfPos next_2 = next_1;
                    next_2.Play(m2);
                    if (next_2.IsGameOver())
                        moves.push_back({ m1, m2 });
                    else
                        for (const Move& m3 : next_2.PossibleMoves(d))
                        {
                            HalfPos next_3 = next_2;
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
            HalfPos next_1 = *this;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                moves.push_back({ m1 });
            else
                for (const Move& m2 : next_1.PossibleMoves(dice.second))
                    moves.push_back({ m1, m2 });
        }
        for (const Move& m1 : PossibleMoves(dice.second))
        {
            HalfPos next_1 = *this;
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

void HalfPos::Play(const Move& move)
{
    fields[move.from - 1]--;
    if (move.to != off)
        fields[move.to - 1]++;
}

std::string to_string(const HalfPos& pos)
{
    std::string str;
    for (int i = 0; i < bar; i++)
        str += std::to_string(pos.Checkers(i)) + ' ';
    str += "bar: " + std::to_string(pos.Checkers(bar));
    return str;
}

HalfPos Play(HalfPos pos, const Moves& moves)
{
    for (const Move& move : moves)
        pos.Play(move);
    return pos;
}

std::size_t std::hash<HalfPos>::operator()(const HalfPos& pos) const
{
    uint64_t sum = 0;
    for (int i = 0; i < 16; i++)
        sum += static_cast<uint64_t>(pos.Checkers(i)) << (4 * i);
    return std::hash<uint64_t>()(sum);
}