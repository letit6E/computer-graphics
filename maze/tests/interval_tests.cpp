#include <gtest/gtest.h>
#include "../src/interval_tree/interval-tree.hpp"

TEST(Interval_test, query_test) {
    std::vector<MazeSegment> x = {
            {1, 3, 0},
            {1, 3, 3},
            {1.5, 2.5, 1},
            {1.5, 2.5, 2},
            {2, 2.7, 5},
            {2, 2.7, 7},
            {1, 2, 3},
            {1, 4, 3},
            {1, 2, 3},
    };
    IntervalTree t = x;

    ASSERT_EQ(t.query(1.5, 4), 7);
    ASSERT_EQ(t.query(2.6, 5), 4);
    ASSERT_EQ(t.query(4, 3), 1);
    ASSERT_EQ(t.query(1, 1), 1);
    ASSERT_EQ(t.query(2, 3), 7);
    ASSERT_EQ(t.query(2, 2), 3);
    ASSERT_EQ(t.query(2, 5), 8);
}