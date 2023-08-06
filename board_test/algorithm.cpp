#include <gtest/gtest.h>
#include "board/board.h"
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
