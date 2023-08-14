#include <gtest/gtest.h>
#include "core/core.h"

TEST(Move, compare)
{
    Move A(3, 1);
    Move B(3, 2);

    EXPECT_TRUE(A == A);
    EXPECT_FALSE(A == B);

    EXPECT_TRUE(A != B);
    EXPECT_FALSE(A != A);

    EXPECT_TRUE(A < B);
    EXPECT_FALSE(A < A);

    EXPECT_TRUE(A <= A);
    EXPECT_TRUE(A <= B);
    EXPECT_FALSE(B <= A);

    EXPECT_TRUE(A >= A);
    EXPECT_TRUE(B >= A);
    EXPECT_FALSE(A >= B);

    EXPECT_TRUE(B > A);
    EXPECT_FALSE(A > A);
}

TEST(Move, to_string)
{
    EXPECT_EQ(to_string(Move(3, off)), "3/off");
    EXPECT_EQ(to_string(Move(3, 1)), "3/1");
    EXPECT_EQ(to_string(Move(bar, 24)), "bar/24");
}

TEST(Moves, to_string)
{
    Moves moves{ {3,off}, {3,1}, {bar,24} };
    EXPECT_EQ(to_string(moves), "3/off 3/1 bar/24");
}
