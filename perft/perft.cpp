#include "core/core.h"
#include <cstdint>
#include <format>
#include <iostream>

int64_t PossibleMoves(const Position& pos, int pips)
{
    int64_t sum = 0;
    if (pos.Checkers(bar) > 0 && !pos.IsBlocked(bar - pips))
        return 1;

    // On board
    for (int i = pips + 1; i < bar; i++)
        if (pos.Checkers(i) > 0 && !pos.IsBlocked(i - pips))
            sum++;

    if (pos.CanBearOff())
    {
        if (pos.Checkers(pips) > 0)
            sum++;
        else if (sum == 0)
            for (int i = pips - 1; i > 0; i--)
                if (pos.Checkers(i) > 0)
                    return 1;
    }

    return sum;
}

int64_t PossibleMoves(const Position& pos, const Dice& dice)
{
    int64_t sum = 0;
    if (dice.IsPair())
    {
        int8_t d = dice.first;
        for (const Move& m1 : pos.PossibleMoves(d))
        {
            Position next_1 = pos;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                sum++;
            else
                for (const Move& m2 : next_1.PossibleMoves(d))
                {
                    Position next_2 = next_1;
                    next_2.Play(m2);
                    if (next_2.IsGameOver())
                        sum++;
                    else
                        for (const Move& m3 : next_2.PossibleMoves(d))
                        {
                            Position next_3 = next_2;
                            next_3.Play(m3);
                            if (next_3.IsGameOver())
                                sum++;
                            else
                                sum += PossibleMoves(next_3, d);
                        }
                }
        }
    }
    else
    {
        for (const Move& m1 : pos.PossibleMoves(dice.first))
        {
            Position next_1 = pos;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                sum++;
            else
                sum += PossibleMoves(next_1, dice.second);
        }
        for (const Move& m1 : pos.PossibleMoves(dice.second))
        {
            Position next_1 = pos;
            next_1.Play(m1);
            if (next_1.IsGameOver())
                sum++;
            else
                sum += PossibleMoves(next_1, dice.first);
        }
    }
    return sum;
}

int64_t perft_1(const Position& pos)
{
    int64_t sum = 0;
	for (const Dice& dice : AllDiceConfigs())
		sum += PossibleMoves(pos, dice);
	return sum;
}

int64_t perft(const Position& pos, int depth)
{
	if (depth == 1)
		return perft_1(pos);

	int64_t sum = 0;
	for (const Dice& dice : AllDiceConfigs())
		for (const Moves& moves : pos.PossibleMoves(dice))
			sum += perft(Play(pos, moves), depth - 1);
	return sum;
}

int64_t perft_parallel(const Position& pos, int depth)
{
    if (depth == 0)
        return 1;
    if (depth == 1)
        return perft_1(pos);

	std::vector<Position> positions;
	for (const Dice& dice : AllDiceConfigs())
		for (const Moves& moves : pos.PossibleMoves(dice))
			positions.push_back(Play(pos, moves));

	int64_t sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < positions.size(); i++)
		sum += perft(positions[i], depth - 1);
	return sum;
}

int main(int argc, char* argv[])
{
	std::locale::global(std::locale(""));

	for (int depth = 0; depth < 10; depth++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		int64_t games = perft_parallel(Position::Start(), depth);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() / 1'000.0;
		std::cout << std::format("{}: {:L} ({} s)\n", depth, games, duration);
	}
	return 0;
}
