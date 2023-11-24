#include <gtest/gtest.h>
#include <iostream>
#include "../src/wavelet_tree/wavelet-tree.hpp"

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

TEST(Wavelet_Tests, equal_count_test) {
    std::vector<double> x = {3, 1, 2, 4, 2, -1, 4, 1, 10, 3, 2, 1, 10, 39, 3};
    auto tree = WaveletTree(x);

    ASSERT_EQ(tree.equal_count(0, 4, 2), 2);
    ASSERT_EQ(tree.equal_count(0, x.size() - 1, 3), 3);
    ASSERT_EQ(tree.equal_count(3, 2, 1), 0);
    ASSERT_EQ(tree.equal_count(3, 1000, 10), 2);
    ASSERT_EQ(tree.equal_count(0, 1, 1), 1);
    ASSERT_EQ(tree.equal_count(0, 0, 3), 1);
    ASSERT_EQ(tree.equal_count(1, 1, 3), 0);
    ASSERT_EQ(tree.equal_count(1, 1, 1), 1);
    ASSERT_EQ(tree.equal_count(x.size() - 1, x.size() - 1, 3), 1);
    ASSERT_EQ(tree.equal_count(x.size() - 1, x.size() - 1, 3.1), 0);
}

TEST(Wavelet_Tests, lte_count_pair_test) {
    std::vector<std::pair<double, size_t>> x = {{3,  7},
                                                {1,  3},
                                                {2,  1},
                                                {4,  7},
                                                {0,  9},
                                                {-1, 415},
                                                {4,  578},
                                                {1,  99},
                                                {10, 1},
                                                {4,  2},
                                                {2,  3},
                                                {1,  4},
                                                {10, 5},
                                                {39, 1},
                                                {12, 2}};
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

TEST(Wavelet_Tests, equal_count_pair_test) {
    std::vector<std::pair<double, size_t>> x = {{3,  7},
                                                {1,  3},
                                                {2,  1},
                                                {4,  7},
                                                {2,  9},
                                                {-1, 415},
                                                {4,  578},
                                                {1,  99},
                                                {10, 1},
                                                {3,  2},
                                                {2,  3},
                                                {1,  4},
                                                {10, 5},
                                                {39, 1},
                                                {3, 2}};
    auto tree = WaveletTree(x);

    ASSERT_EQ(tree.equal_count(0, 4, 2), 2);
    ASSERT_EQ(tree.equal_count(0, x.size() - 1, 3), 3);
    ASSERT_EQ(tree.equal_count(3, 2, 1), 0);
    ASSERT_EQ(tree.equal_count(3, 1000, 10), 2);
    ASSERT_EQ(tree.equal_count(0, 1, 1), 1);
    ASSERT_EQ(tree.equal_count(0, 0, 3), 1);
    ASSERT_EQ(tree.equal_count(1, 1, 3), 0);
    ASSERT_EQ(tree.equal_count(1, 1, 1), 1);
    ASSERT_EQ(tree.equal_count(x.size() - 1, x.size() - 1, 3), 1);
    ASSERT_EQ(tree.equal_count(x.size() - 1, x.size() - 1, 3.1), 0);
}

TEST(Wavelet_Tests, lte_sum_pair_test) {
    std::vector<std::pair<double, size_t>> x = {{3,  7},
                                                {1,  3},
                                                {2,  1},
                                                {4,  7},
                                                {0,  9},
                                                {-1, 415},
                                                {4,  578},
                                                {1,  99},
                                                {10, 1},
                                                {4,  2},
                                                {2,  3},
                                                {1,  4},
                                                {10, 5},
                                                {39, 1},
                                                {12, 2}};
    auto tree = WaveletTree(x);

    ASSERT_EQ(tree.lte_xor(0, 4, 2), 3 ^ 1 ^ 9);
    ASSERT_EQ(tree.lte_xor(0, x.size() - 1, 3), 7 ^ 3 ^ 1 ^ 9 ^ 415 ^ 99 ^ 3 ^ 4);
    ASSERT_EQ(tree.lte_xor(3, 2, 1), 0);
    ASSERT_EQ(tree.lte_xor(3, 1000, 1), 415 ^ 9 ^ 99 ^ 4);
    ASSERT_EQ(tree.lte_xor(0, 1, 2), 3);
    ASSERT_EQ(tree.lte_xor(0, 0, 2), 0);
    ASSERT_EQ(tree.lte_xor(1, 1, 2), 3);
    ASSERT_EQ(tree.lte_xor(x.size() - 1, x.size() - 1, 13), 2);
    ASSERT_EQ(tree.lte_xor(x.size() - 1, x.size() - 1, 11), 0);
}

