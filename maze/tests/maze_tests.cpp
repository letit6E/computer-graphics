

#include <gtest/gtest.h>
#include "../src/maze/maze.hpp"

TEST(MazeTest, SplitTest) {
    auto tmp = Maze();

    std::vector<std::vector<double>> input = {
            {1,   1,  1,  2},
            {1,   2,  3,  2},
            {3,   2,  3,  1},
            {1,   1,  3,  1},
            {10,  10, 15, 10},
            {15,  15, 15, 20},
            {19,  30, 18, 30},
            {18,  30, 17, 30},
            {1,   1,  -4, 1},
            {-10, 1,  -4, 1}
    };
    for (const auto &str: input) {
        double x1 = str[0];
        double y1 = str[1];
        double x2 = str[2];
        double y2 = str[3];

        auto result = tmp.add_edge(Point{x1, y1}, Point{x2, y2});
        ASSERT_TRUE(result.is_ok());
    }

    tmp.split();
    auto comps = tmp.get_components();

    ASSERT_TRUE(
            (comps == std::vector<std::set<Point>>{
                    {{-10, 1},  {-4, 1},  {1,  1}, {1, 2}, {3, 1}, {3, 2}},
                    {{10,  10}, {15, 10}},
                    {{15,  15}, {15, 20}},
                    {{17,  30}, {18, 30}, {19, 30}}
            }));
}

TEST(MazeTest, LeafTest) {
    auto tmp = Maze();

    std::vector<std::vector<double>> input = {
            {1,   1,  1,  2},
            {1,   2,  3,  2},
            {3,   2,  3,  1},
            {1,   1,  3,  1},
            {10,  10, 15, 10},
            {15,  15, 15, 20},
            {19,  30, 18, 30},
            {18,  30, 17, 30},
            {1,   1,  -4, 1},
            {-10, 1,  -4, 1}
    };
    for (const auto &str: input) {
        double x1 = str[0];
        double y1 = str[1];
        double x2 = str[2];
        double y2 = str[3];

        auto result = tmp.add_edge(Point{x1, y1}, Point{x2, y2});
    }

    tmp.split();
    tmp.remove_leaf_edges();

    ASSERT_TRUE(
            (tmp.get_edges() == std::vector<std::pair<Point, Point>>{{{1, 1}, {1, 2}},
                                                                     {{1, 1}, {3, 1}},
                                                                     {{1, 2}, {3, 2}},
                                                                     {{3, 2}, {3, 1}}})
    );
}
