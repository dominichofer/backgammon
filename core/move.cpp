#include "move.h"
#include "algorithm.h"

std::string to_string(int8_t pip)
{
	switch (pip)
	{
	case off:
		return "off";
	case bar:
		return "bar";
	default:
		return std::to_string(pip);
	}
}

std::string to_string(const Move& move)
{
    return to_string(move.from) + '/' + to_string(move.to);
}

std::string to_string(const Moves& moves)
{
	return join(' ', moves, [](const Move& m) { return to_string(m); });
}
