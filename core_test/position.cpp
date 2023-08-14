#include <gtest/gtest.h>
#include "core/core.h"
#include <algorithm>
#include <vector>

static void SameMoves(Moves l, Moves r)
{
	std::ranges::sort(l);
	std::ranges::sort(r);
	EXPECT_EQ(l, r);
}

static void SameMoves(std::vector<Moves> l, std::vector<Moves> r)
{
	std::ranges::sort(l);
	std::ranges::sort(r);
	EXPECT_EQ(l, r);
}

TEST(Position, Player)
{
	auto pos = Position({ -2, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,-1,-1, 3 });
	EXPECT_EQ(pos.Player(), HalfPos({ 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 3 }));
	EXPECT_EQ(pos.Opponent(), HalfPos({ 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 2 }));
}

TEST(Position, Checkers)
{
	auto pos = Position({ 0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 2 });
	EXPECT_EQ(pos.Checkers(1), 1);
	EXPECT_EQ(pos.Checkers(bar), 2);
	EXPECT_EQ(pos.Checkers(bar), 2);
}

TEST(Position, CanBearOff)
{
	EXPECT_TRUE(Position({ 0, 1,0,0,0,0,0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_TRUE(Position({ 0, 0,1,0,0,0,0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_TRUE(Position({ 0, 0,0,1,0,0,0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_TRUE(Position({ 0, 0,0,0,1,0,0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_TRUE(Position({ 0, 0,0,0,0,1,0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_TRUE(Position({ 0, 0,0,0,0,0,1, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());

	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());

	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0 }).CanBearOff());

	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0 }).CanBearOff());
	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0 }).CanBearOff());

	EXPECT_FALSE(Position({ 0, -1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1 }).CanBearOff());
}

TEST(Position, IsEndgame)
{
	EXPECT_TRUE(Position({ 0, 0,0,0,0,0,0, 1,-1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).IsEndgame());
	EXPECT_FALSE(Position({ 0, 0,0,0,0,0,0, -1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).IsEndgame());
}

TEST(Position, IsGameOver)
{
	EXPECT_TRUE(Position({ 0, 0,0,0,0,0,0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).IsGameOver());
	EXPECT_TRUE(Position({ 0, 0,0,0,0,0,0, 0,0,-1,-1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).IsGameOver());
	EXPECT_FALSE(Position({ 0, 0,0,0,0,0,0, 1,1,-1,-1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }).IsGameOver());
}

TEST(Position, PossibleMoves_pips_on_bar)
{
	auto pos = Position({ 0, 1,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1 });
	auto moves = Moves{ {bar,24} };
	SameMoves(pos.PossibleMoves(1), moves);
}

TEST(Position, PossibleMoves_pips_on_field)
{
	Position pos;
	Moves moves;

	pos = Position({ 0, 1,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {7,6} };
	SameMoves(pos.PossibleMoves(1), moves);

	pos = Position({ 0, 1,0,0,0,0,-2, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{};
	SameMoves(pos.PossibleMoves(1), moves);

	pos = Position({ 0, 1,0,0,0,0,0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {7,6}, {8,7} };
	SameMoves(pos.PossibleMoves(1), moves);

	pos = Position({ 0, 1,0,0,0,0,-2, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {8,7} };
	SameMoves(pos.PossibleMoves(1), moves);
}

TEST(Position, PossibleMoves_pips_bear_off)
{
	Position pos;
	Moves moves;

	pos = Position({ 0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {1,off}, {2,1} };
	SameMoves(pos.PossibleMoves(1), moves);

	pos = Position({ 0, -1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {2,1} };
	SameMoves(pos.PossibleMoves(1), moves);

	pos = Position({ 0, -2,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{};
	SameMoves(pos.PossibleMoves(1), moves);

	pos = Position({ 0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {2,off} };
	SameMoves(pos.PossibleMoves(2), moves);

	pos = Position({ 0, -2,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {2,off} };
	SameMoves(pos.PossibleMoves(2), moves);

	pos = Position({ 0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	moves = Moves{ {2,off} };
	SameMoves(pos.PossibleMoves(3), moves);
}

TEST(Position, PossibleMoves_dice_on_bar)
{
	Position pos;
	std::vector<Moves> moves;

	pos = Position({ 0, 1,0,0,0,0,0, 1,0,0,0,0,-1, 0,0,0,0,0,0, 0,0,0,0,0,0, 1 });
	moves = std::vector{
		Moves{{bar,24}, {24,22}},
		Moves{{bar,24}, {7,5}},
		Moves{{bar,23}, {23,22}},
		Moves{{bar,23}, {7,6}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 2)), moves);

	pos = Position({ 0, 1,0,0,0,0,0, 0,0,0,0,0,-1, 0,0,0,0,0,0, 0,0,0,0,0,0, 2 });
	moves = std::vector{ Moves{{bar,24}, {bar,23}}, Moves{{bar,23}, {bar,24}} };
	SameMoves(pos.PossibleMoves(Dice(1, 2)), moves);
}

TEST(Position, PossibleMoves_dice_on_field)
{
	Position pos;
	std::vector<Moves> moves;

	pos = Position({ 0, 1,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector{
		Moves{{7,6}, {6,4}},
		Moves{{7,5}, {5,4}},
		Moves{{7,5}, {1,off}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 2)), moves);

	pos = Position({ 0, 1,0,0,0,0,0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector{
		Moves{{7,6}, {6,4}},
		Moves{{7,6}, {8,6}},
		Moves{{7,5}, {5,4}},
		Moves{{7,5}, {8,7}},
		Moves{{8,7}, {7,5}},
		Moves{{8,6}, {7,6}},
		Moves{{8,6}, {6,5}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 2)), moves);

	pos = Position({ 0, 1,0,0,0,0,0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector{
		Moves{{7,6}, {6,5}, {5,4}, {4,3}},
		Moves{{7,6}, {6,5}, {5,4}, {8,7}},
		Moves{{7,6}, {6,5}, {8,7}, {5,4}},
		Moves{{7,6}, {6,5}, {8,7}, {7,6}},
		Moves{{7,6}, {8,7}, {6,5}, {5,4}},
		Moves{{7,6}, {8,7}, {6,5}, {7,6}},
		Moves{{7,6}, {8,7}, {7,6}, {6,5}},
		Moves{{7,6}, {8,7}, {7,6}, {1,off}},
		Moves{{8,7}, {7,6}, {6,5}, {5,4}},
		Moves{{8,7}, {7,6}, {6,5}, {7,6}},
		Moves{{8,7}, {7,6}, {7,6}, {6,5}},
		Moves{{8,7}, {7,6}, {7,6}, {1,off}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 1)), moves);

	pos = Position({ 0, 1,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector<Moves>{ Moves{{7,1}, {1,off}, {1,off}} };
	SameMoves(pos.PossibleMoves(Dice(6, 6)), moves);
}

TEST(Position, PossibleMoves_dice_bear_off)
{
	Position pos;
	std::vector<Moves> moves;

	pos = Position({ 0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector{
		Moves{{1,off}, {2,1}, {1,off}},
		Moves{{2,1}, {1,off}, {1,off}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 1)), moves);

	pos = Position({ 0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector{
		Moves{{1,off}, {2,off}},
		Moves{{2,off}, {1,off}},
		Moves{{2,1}, {1,off}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 2)), moves);

	pos = Position({ 0, 1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });
	moves = std::vector{
		Moves{{1,off}, {2,off}},
		Moves{{2,off}, {1,off}},
		Moves{{2,1}, {1,off}}
	};
	SameMoves(pos.PossibleMoves(Dice(1, 3)), moves);
}

TEST(Position, Play_hit)
{
	auto pos = Position({ 0, 0,0,0,0,0,0, -1,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 });
	pos.Play({ 8,7 });
	EXPECT_EQ(pos, Position({ -1, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0 }));
}
