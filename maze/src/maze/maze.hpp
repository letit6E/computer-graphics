#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include "point.hpp"
#include "result.hpp"

enum class MazeError {
    NOT_RECTILINEAR
};

class Maze {
public:
    Result<bool, MazeError> add_edge(const Point &fst, const Point &snd) {
        if (fst.x != snd.x && fst.y != snd.y) {
            return Err(MazeError::NOT_RECTILINEAR);
        }

        size_t fst_index = add_vertex(fst);
        size_t snd_index = add_vertex(snd);

        graph[fst_index].push_back(snd_index);
        graph[snd_index].push_back(fst_index);
        return Ok(true);
    }

    void split() {
        std::vector<int> comps(vertices.size(), -1);
        int cur_component = 0;
        for (size_t v = 0; v < vertices.size(); ++v) {
            if (comps[v] != -1) continue;

            std::vector<size_t> dfs_queue = {v};
            while (!dfs_queue.empty()) {
                size_t cur = dfs_queue.back();
                comps[cur] = cur_component;
                dfs_queue.pop_back();

                for (const size_t &u: graph[cur]) {
                    if (comps[u] == -1) {
                        dfs_queue.push_back(u);
                    }
                }
            }

            ++cur_component;
        }

        components = std::vector<std::set<Point>>(cur_component);
        for (size_t v = 0; v < vertices.size(); ++v) {
            components[comps[v]].insert(vertices[v]);
        }
    }


    std::vector<std::set<Point>> get_components() {
        auto result = components;
        return result;
    }

private:
    size_t add_vertex(const Point &v) {
        const auto it = vertices_indexes.find(v);
        if (it == vertices_indexes.cend()) {
            size_t new_index = vertices.size();
            vertices_indexes[v] = new_index;
            vertices.push_back(v);
            graph.emplace_back();
            return new_index;
        }
        return it->second;
    }


    std::vector<std::pair<Point, Point>> edges;
    std::vector<Point> vertices;
    std::map<Point, size_t> vertices_indexes;
    std::vector<std::vector<size_t>> graph;
    std::vector<std::set<Point>> components;
};