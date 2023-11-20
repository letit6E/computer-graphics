class WaveletTree {
private:
    size_t n;
    double lo, hi;
    WaveletTree *left, *right;
    std::vector<size_t> prefix_cnt;
public:

    WaveletTree(std::vector<double> vec) {
        n = vec.size();
        if (vec.empty()) {
            lo = DBL_MAX;
            hi = DBL_MIN;
            left = nullptr;
            right = nullptr;
            return;
        }
        lo = *std::min_element(vec.begin(), vec.end());
        hi = *std::max_element(vec.begin(), vec.end());
        prefix_cnt.resize(vec.size() + 1);

        if (hi == lo) {
            prefix_cnt[0] = 0;
            for (size_t i = 1; i <= vec.size(); ++i) {
                prefix_cnt[i] = i;
            }
            return;
        }

        double mid = (lo + hi) / 2;
        for (size_t i = 1; i <= vec.size(); ++i) {
            prefix_cnt[i] = prefix_cnt[i - 1] + (vec[i - 1] <= mid);
        }

        std::vector<double> left_vec, right_vec;
        for (const double& elem : vec) {
            if (elem <= mid) left_vec.push_back(elem);
            else right_vec.push_back(elem);
        }

        left = new WaveletTree(left_vec);
        right = new WaveletTree(right_vec);
    }

    size_t lte_count(int l, int r, double k) {
        if (l > r || k < lo) return 0;
        l = std::max(l, 0);
        r = std::min(r, static_cast<int>(n) - 1);
        if (hi <= k) return r - l + 1;

        int left_cnt = static_cast<int>(prefix_cnt[l]), right_cnt = static_cast<int>(prefix_cnt[r + 1]);
        return left->lte_count(left_cnt, right_cnt - 1, k) + right->lte_count(l - left_cnt, r - right_cnt, k);
    }

    size_t equal_count(int l, int r, double k) {
        if (l > r || k < lo || k > hi) return 0;
        l = std::max(l, 0);
        r = std::min(r, static_cast<int>(n) - 1);
        if (lo == hi) return r - l + 1;

        int left_cnt = static_cast<int>(prefix_cnt[l]), right_cnt = static_cast<int>(prefix_cnt[r + 1]);

        if (k <= (lo + hi) / 2) {
            return left->equal_count(left_cnt, right_cnt - 1, k);
        } else {
            return right->equal_count(l - left_cnt, r - right_cnt, k);
        }
    }

};

