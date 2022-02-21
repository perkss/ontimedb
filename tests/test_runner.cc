#include <iostream>
#include <gtest/gtest.h>

extern "C" {
#include "../db/page.h" // What is missing in CMAKE to import this direct
}

TEST(TESTDB, TestPageGet) {
    ASSERT_EQ(5, getPage());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
