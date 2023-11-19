#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

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
        edges.emplace_back(fst, snd);
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

    void remove_leaf_edges() {
        for (size_t v = 0; v < graph.size(); ++v) {
            if (graph[v].size() == 1) {
                size_t prev = v;
                size_t cur = graph[v][0];
                graph[v] = {};
                while (graph[cur].size() == 2) {
                    size_t next = (graph[cur][0] == prev) ? graph[cur][1] : graph[cur][0];
                    graph[cur] = {};
                    prev = cur;
                    cur = next;
                }

                graph[cur].erase(std::remove(graph[cur].begin(), graph[cur].end(), prev), graph[cur].end());
            }
        }

        std::vector<int> comps(vertices.size());
        for (int i = 0; i < static_cast<int>(components.size()); ++i) {
            for (const Point &pt: components[i]) {
                comps[vertices_indexes[pt]] = i;
            }
        }

        std::set<Point> removed;
        for (size_t v = 0; v < graph.size(); ++v) {
            if (graph[v].empty()) {
                removed.insert(vertices[v]);
                components[comps[v]].erase(vertices[v]);
            }
        }

        std::vector<std::set<Point>> new_components;
        for (const auto &st: components) {
            if (!st.empty()) new_components.push_back(st);
        }
        components = new_components;
    }

    void construct_halls() {
        for (auto& component : components) {
            Point start_vertex = *component.begin();
            for (const auto& [x, y] : component) {
                if (y < start_vertex.y || y == start_vertex.y && x > start_vertex.x) {
                    start_vertex = {x, y};
                }
            }

            size_t start_index = vertices_indexes[start_vertex];
            int cur_direction = 3; // 0 for up, 3 for right, 2 for down, 1 for left

            std::set<Point> new_component;
            size_t cur_index = start_index;
            Point cur_vertex = start_vertex;
            do {
                std::priority_queue<std::pair<int, Point>> directions;
                for (const size_t& index : graph[cur_index]) {
                    Point pt = vertices[index];
                    int priority;
                    if (pt.x == cur_vertex.x) {
                        if (pt.y > cur_vertex.y) {
                            priority = (2 + cur_direction) % 4;
                        } else {
                            priority = (cur_direction) % 4;
                        }
                    } else {
                        if (pt.x > cur_vertex.x) {
                            priority = (3 + cur_direction) % 4;
                        } else {
                            priority = (1 + cur_direction) % 4;
                        }
                    }
                    directions.emplace(priority, pt);
                }

                auto [priority, next_vertex] = directions.top();
                size_t next_index = vertices_indexes[next_vertex];
                graph[cur_index] = {next_index};
                if (next_vertex.x == cur_vertex.x) {
                    if (next_vertex.y > cur_vertex.y) {
                        cur_direction = 0;
                    } else {
                        cur_direction = 2;
                    }
                } else {
                    if (next_vertex.x > cur_vertex.x) {
                        cur_direction = 3;
                    } else {
                        cur_direction = 1;
                    }
                }
                cur_index = next_index;
                cur_vertex = next_vertex;

                new_component.insert(next_vertex);
            } while (cur_index != start_index);

            for (const Point& pt : component) {
                if (new_component.find(pt) == new_component.cend()) {
                    graph[vertices_indexes[pt]] = {};
                }
            }
            component = new_component;
        }
    }

    std::vector<std::pair<Point, Point>> get_edges() {
        auto result = edges;
        return edges;
    }

    std::vector<Point> get_vertices() {
        auto result = vertices;
        return result;
    }

    std::map<Point, size_t> get_vertices_indexes() {
        auto result = vertices_indexes;
        return result;
    }

    std::vector<std::vector<size_t>> get_graph() {
        auto result = graph;
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