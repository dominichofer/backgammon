#include <gtest/gtest.h>
#include "search/search.h"

TEST(EndgameTable, Simple)
{
    EndgameTable table(1);
	auto pos = Position({ 0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,-1, 0 });

	EXPECT_TRUE(table.Contains(pos));
	EXPECT_EQ(table.BearingOffProbDist(pos.Player()), ProbDist({ 0.0, 1.0 }));
	EXPECT_EQ(table.WinProbability(pos), 1.0);
}

TEST(EndgameTable, Complex)
{
	EndgameTable table(3);
	auto pos = Position({ 0, 1,2,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,-1,-2,-1, 0 });

	EXPECT_TRUE(table.Contains(pos));
	EXPECT_FLOAT_EQ(table.WinProbability(pos), 1.0);
}
