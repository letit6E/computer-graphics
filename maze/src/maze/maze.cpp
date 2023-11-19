#include "maze.hpp"

size_t Maze::add_vertex(const Point &v) {
    const auto it = vertices_indexes.find(v);
    if (it == vertices_indexes.cend()) {
        size_t new_index = vertices_indexes.size();
        vertices_indexes[v] = new_index;
        vertices.push_back(v);
        graph.emplace_back();
        return new_index;
    }
    return it->second;
}

Result<bool, MazeError> Maze::add_edge(const Point &fst, const Point &snd) {
    if (fst.x != snd.x && fst.y != snd.y) {
        return Err(MazeError::NOT_RECTILINEAR);
    }

    size_t fst_index = add_vertex(fst);
    size_t snd_index = add_vertex(snd);

    graph[fst_index].push_back(snd_index);
    graph[snd_index].push_back(fst_index);
}