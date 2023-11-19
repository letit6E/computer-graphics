

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

    auto graph = tmp.get_graph();
    auto map = tmp.get_vertices_indexes();
    ASSERT_TRUE(
            (
                    graph[map[{-10, 1}]].empty() &&
                    graph[map[{-4, 1}]].empty() &&
                    graph[map[{10, 10}]].empty() &&
                    graph[map[{15, 10}]].empty() &&
                    graph[map[{15, 15}]].empty() &&
                    graph[map[{15, 20}]].empty() &&
                    graph[map[{17, 30}]].empty() &&
                    graph[map[{18, 30}]].empty() &&
                    graph[map[{19, 30}]].empty()
            )
    );
}

TEST(MazeTest, HallTest) {
    auto tmp = Maze();

    std::vector<std::vector<double>> input = {
            {1, 1, 1, 5},
            {1, 5, 2, 5},
            {2, 5, 2, 8},
            {2, 8, 1, 8},
            {2, 8, 2, 10},
            {2, 8, 5, 8},
            {5, 8, 5, 9},
            {5, 8, 8, 8},
            {5, 7, 5, 3},
            {5, 3, 8, 3},
            {5, 3, 5, 1},
            {5, 3, 4, 3},
            {5, 8, 5, 7},
            {5, 7, 4, 7},
            {4, 7, 3, 7},
            {3, 7, 3, 5},
            {3, 5, 4, 5},
            {4, 5, 4, 7},
            {4, 3, 4, 2},
            {4, 2, 3, 2},
            {3, 2, 3, 1},
            {3, 1, 1, 1},
            {4, 3, 3, 3},
            {3, 3, 3, 4},
            {3, 4, 2, 4},
            {2, 5, 2, 4},
            {2, 2, 2, 4},
            {2, 2, 3, 2}
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
    tmp.construct_halls();

    auto vertices = tmp.get_vertices();
    auto graph = tmp.get_graph();
    std::vector<std::pair<Point, Point>> actual_graph;
    for (size_t v = 0; v < graph.size(); ++v) {
        Point fst = vertices[v];
        for (const size_t &u: graph[v]) {
            Point snd = vertices[u];
            actual_graph.emplace_back(fst, snd);
        }
    }

    ASSERT_TRUE(
            (actual_graph == std::vector<std::pair<Point, Point>>{
                    {{1, 1}, {3, 1}},
                    {{1, 5}, {1, 1}},
                    {{2, 5}, {1, 5}},
                    {{2, 8}, {2, 5}},
                    {{5, 8}, {2, 8}},
                    {{5, 7}, {5, 8}},
                    {{5, 3}, {5, 7}},
                    {{4, 3}, {5, 3}},
                    {{4, 2}, {4, 3}},
                    {{3, 2}, {4, 2}},
                    {{3, 1}, {3, 2}}
            })
    );
}
