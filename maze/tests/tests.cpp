//
// Created by letit6E on 18.11.2023.
//

#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(a, b) {
    EXPECT_EQ(3, 3);
}