#include <gtest/gtest.h>

TEST(OnTimeDbibTest, BasicAssertions
) {
// Expect two strings not to be equal.
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(5 * 5, 25);
}
