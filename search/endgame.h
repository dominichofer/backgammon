#pragma once
#include "core/core.h"
#include <unordered_map>

class EndgameTable
{
	int fields, checkers;
	std::unordered_map<HalfPos, ProbDist> pd;
public:
	explicit EndgameTable(int fields, int checkers = 15);

	ProbDist BearingOffProbDist(const HalfPos&) const;
	bool Contains(const HalfPos&) const;
	bool Contains(const Position&) const;
	double WinProbability(const Position&) const;
};
