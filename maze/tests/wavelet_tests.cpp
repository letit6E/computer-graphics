#include <gtest/gtest.h>
#include "../src/wavelet_tree/wavelet_tree.hpp"

TEST(Wavelet_Tests, get_one_test) {
    auto tmp = WaveletTree();
    ASSERT_EQ(tmp.get_one(), 1);
}