#include <gtest/gtest.h>
#include <iostream>
#include "../src/wavelet_tree/wavelet_tree.hpp"

TEST(Wavelet_Tests, lte_count_test) {
    std::vector<double> x = {3, 1, 2, 4, 0, -1, 4, 1, 10, 4, 2, 1, 10, 39, 12};
    auto tree = WaveletTree(x);

    ASSERT_EQ(tree.lte_count(0, 4, 2), 3);
    ASSERT_EQ(tree.lte_count(0, x.size() - 1, 3), 8);
    ASSERT_EQ(tree.lte_count(3, 2, 1), 0);
    ASSERT_EQ(tree.lte_count(3, 1000, 1), 4);
    ASSERT_EQ(tree.lte_count(0, 1, 2), 1);
    ASSERT_EQ(tree.lte_count(0, 0, 2), 0);
    ASSERT_EQ(tree.lte_count(1, 1, 2), 1);
    ASSERT_EQ(tree.lte_count(1, 1, 2), 1);
    ASSERT_EQ(tree.lte_count(x.size() - 1, x.size() - 1, 13), 1);
    ASSERT_EQ(tree.lte_count(x.size() - 1, x.size() - 1, 11), 0);
}