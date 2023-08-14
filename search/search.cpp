#include "search.h"

static EndgameTable table(6);

ProbDist EndScore(const Position& pos)
{
    bool all_positive = true;
    bool all_negative = true;
    for (int i = off; i <= bar; i++)
    {
        int f = pos.Checkers(i);
        if (f < 0)
            all_positive = false;
        if (f > 0)
            all_negative = false;
    }
    if (all_positive)
        return ProbDist{ {1.0} };
    if (all_negative)
        return ProbDist{ {0.0} };
}

ProbDist Eval(const Position& pos)
{
	return ProbDist{};
}