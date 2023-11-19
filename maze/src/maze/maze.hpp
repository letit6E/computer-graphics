#include <vector>
#include <map>
#include <algorithm>

#include "point.hpp"
#include "result.hpp"

enum class MazeError {
    NOT_RECTILINEAR
};

class Maze {
public:
    Result<bool, MazeError> add_edge(const Point &fst, const Point &snd);

private:
    size_t add_vertex(const Point& v);

    std::vector<std::pair<Point, Point>> edges;
    std::vector<Point> vertices;
    std::map<Point, size_t> vertices_indexes;
    std::vector<std::vector<size_t>> graph;
};