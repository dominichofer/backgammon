#include <gtest/gtest.h>
#include "core/core.h"
#include <string>
#include <vector>

TEST(join, string)
{
    EXPECT_EQ(join("-", std::vector{"a", "b"}), "a-b");
}

TEST(join, char)
{
    EXPECT_EQ(join('-', std::vector{"a", "b"}), "a-b");
}

TEST(Binomial, SmallValues)
{
    EXPECT_EQ(Binomial(5, 2), 10);
}

TEST(Binomial, LargeValues)
{
    EXPECT_EQ(Binomial(10, 5), 252);
}

TEST(Binomial, BoundaryValues)
{
    EXPECT_EQ(Binomial(0, 0), 1);
    EXPECT_EQ(Binomial(10, 0), 1);
    EXPECT_EQ(Binomial(10, 10), 1);
}

TEST(Binomial, LargeInput)
{
    EXPECT_EQ(Binomial(50, 25), 126410606437752);
}

TEST(Binomial, EdgeCases)
{
    // Test for edge case where k > n
    EXPECT_EQ(Binomial(5, 6), 0);
}

TEST(MultisetNumber, SmallValues)
{
    EXPECT_EQ(MultisetNumber(15,  1),              1);
    EXPECT_EQ(MultisetNumber(15,  2),             16);
    EXPECT_EQ(MultisetNumber(15,  3),            136);
    EXPECT_EQ(MultisetNumber(15,  4),            816);
    EXPECT_EQ(MultisetNumber(15,  5),          3'876);
    EXPECT_EQ(MultisetNumber(15,  6),         15'504);
    EXPECT_EQ(MultisetNumber(15,  7),         54'264);
    EXPECT_EQ(MultisetNumber(15,  8),        170'544);
    EXPECT_EQ(MultisetNumber(15,  9),        490'314);
    EXPECT_EQ(MultisetNumber(15, 10),      1'307'504);
    EXPECT_EQ(MultisetNumber(15, 11),      3'268'760);
    EXPECT_EQ(MultisetNumber(15, 12),      7'726'160);
    EXPECT_EQ(MultisetNumber(15, 13),     17'383'860);
    EXPECT_EQ(MultisetNumber(15, 14),     37'442'160);
    EXPECT_EQ(MultisetNumber(15, 15),     77'558'760);
    EXPECT_EQ(MultisetNumber(15, 16),    155'117'520);
    EXPECT_EQ(MultisetNumber(15, 17),    300'540'195);
    EXPECT_EQ(MultisetNumber(15, 18),    565'722'720);
    EXPECT_EQ(MultisetNumber(15, 19),  1'037'158'320);
    EXPECT_EQ(MultisetNumber(15, 20),  1'855'967'520);
    EXPECT_EQ(MultisetNumber(15, 21),  3'247'943'160);
    EXPECT_EQ(MultisetNumber(15, 22),  5'567'902'560);
    EXPECT_EQ(MultisetNumber(15, 23),  9'364'199'760);
    EXPECT_EQ(MultisetNumber(15, 24), 15'471'286'560);
    EXPECT_EQ(MultisetNumber(15, 25), 25'140'840'660);
}
