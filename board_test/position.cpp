#include <gtest/gtest.h>
#include "board/board.h"


TEST(HalfPos, Checkers)
{
	EXPECT_EQ(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).Checkers(), 0);
	EXPECT_EQ(HalfPos({1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).Checkers(), 1);
	EXPECT_EQ(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}).Checkers(), 1);
	EXPECT_EQ(HalfPos({1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1}).Checkers(), 25);

	EXPECT_EQ(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}).Checkers(24), 1);
	EXPECT_EQ(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}).CheckersOnBar(), 1);
}

TEST(HalfPos, CanBearOff)
{
	EXPECT_TRUE(HalfPos({1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}).CanBearOff());
}
