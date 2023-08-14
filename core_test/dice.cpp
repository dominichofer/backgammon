#include <gtest/gtest.h>
#include "core/core.h"

TEST(Dice, to_string)
{
	EXPECT_EQ(to_string(Dice(1, 3)), "1-3");
}