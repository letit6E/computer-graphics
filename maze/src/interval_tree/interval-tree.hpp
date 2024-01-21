#include <vector>
#include <random>
#include "maze-segment.hpp"
#include "../wavelet_tree/wavelet-tree.hpp"

class IntervalTree {
private:
    IntervalTree *left = nullptr, *right = nullptr;
    double mid = 0;
    std::vector<MazeSegment> left_segments = {}, right_segments = {};
    WaveletTree left_query = WaveletTree(std::vector<std::pair<double, size_t>>{});
    WaveletTree right_query = WaveletTree(std::vector<std::pair<double, size_t>>{});
public:
    IntervalTree(const std::vector<MazeSegment> &segments) {
        if (segments.empty()) return;

        std::vector<double> coordinates(segments.size() * 2);
        for (size_t i = 0; i < coordinates.size(); i += 2) {
            coordinates[i] = segments[i / 2].down;
            coordinates[i + 1] = segments[i / 2].up;
        }
        mid = mid_element(coordinates);

        std::vector<MazeSegment> left_child, right_child;
        for (const auto &segment: segments) {
            if (segment.up < mid) {
                left_child.push_back(segment);
            } else if (segment.down > mid) {
                right_child.push_back(segment);
            } else {
                left_segments.push_back(segment);
                right_segments.push_back(segment);
            }
        }

        struct {
            bool operator()(const MazeSegment &fst, const MazeSegment &snd) const {
                if (fst.down != snd.down) return fst.down < snd.down;
                return fst.up < snd.up;
            }
        } left_less;

        struct {
            bool operator()(const MazeSegment &fst, const MazeSegment &snd) const {
                if (fst.up != snd.up) return fst.up < snd.up;
                return fst.down < snd.down;
            }
        } right_less;

        std::sort(left_segments.begin(), left_segments.end(), left_less);
        std::sort(right_segments.begin(), right_segments.end(), right_less);

        std::vector<double>
                left_query_vec(left_segments.size()),
                right_query_vec(right_segments.size());
        for (size_t i = 0; i < left_segments.size(); ++i)
            left_query_vec[i] = left_segments[i].arg;
        for (size_t i = 0; i < right_segments.size(); ++i)
            right_query_vec[i] = right_segments[i].arg;

        left_query = WaveletTree(left_query_vec);
        right_query = WaveletTree(right_query_vec);
        left = new IntervalTree(left_child);
        right = new IntervalTree(right_child);
    }

    size_t query(double q, double x) {
        size_t result = 0;
        if (q < mid && left) result = left->query(q, x);
        if (q > mid && right) result = right->query(q, x);

        if (q < mid) {
            int l = -1, r = static_cast<int>(left_segments.size());
            while (r - l > 1) {
                int m = (r + l) / 2;

                if (left_segments[m].down <= q) {
                    l = m;
                } else {
                    r = m;
                }
            }

            if (l == -1) return result;
            return result + left_query.lte_count(0, l, x);
        } else {
            int l = -1, r = static_cast<int>(right_segments.size());
            while (r - l > 1) {
                int m = (r + l) / 2;

                if (right_segments[m].up >= q) {
                    r = m;
                } else {
                    l = m;
                }
            }

            if (r == right_segments.size()) return result;
            return result + right_query.lte_count(r, static_cast<int>(right_segments.size()) - 1, x);
        }
    }

private:
    double mid_element(std::vector<double> coords) {
        size_t middle = coords.size() / 2;
        std::nth_element(coords.begin(), coords.begin() + middle, coords.end());
        return coords[middle];
    }
};