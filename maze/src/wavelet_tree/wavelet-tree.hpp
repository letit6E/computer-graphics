class WaveletTree {
private:
    size_t n;
    double lo, hi;
    WaveletTree *left, *right;
    std::vector<size_t> prefix_cnt;
    std::vector<size_t> prefix_xor;
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
        prefix_xor = std::vector<size_t>(vec.size() + 1, 0);

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

    WaveletTree(std::vector<std::pair<double, size_t>> vec) {
        n = vec.size();
        lo = 1e9;
        hi = -1e9;
        if (vec.empty()) {
            left = nullptr;
            right = nullptr;
            return;
        }

        for (const auto& [x, _] : vec) {
            lo = std::min(lo, x);
            hi = std::max(hi, x);
        }
        prefix_cnt.resize(vec.size() + 1);
        prefix_xor.resize(vec.size() + 1);
        prefix_xor[0] = prefix_cnt[0] = 0;

        if (hi == lo) {
            for (size_t i = 1; i <= vec.size(); ++i) {
                prefix_cnt[i] = i;
                prefix_xor[i] = prefix_xor[i - 1] ^ vec[i - 1].second;
            }
            return;
        }

        double mid = (lo + hi) / 2;
        for (size_t i = 1; i <= vec.size(); ++i) {
            prefix_cnt[i] = prefix_cnt[i - 1] + (vec[i - 1].first <= mid);
            prefix_xor[i] = prefix_xor[i - 1] ^ vec[i - 1].second;
        }

        std::vector<std::pair<double, size_t>> left_vec, right_vec;
        for (const auto& [elem, comp] : vec) {
            if (elem <= mid) left_vec.emplace_back(elem, comp);
            else right_vec.emplace_back(elem, comp);
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

    size_t lte_xor(int l, int r, double k) {
        if (l > r || k < lo) return 0;
        l = std::max(l, 0);
        r = std::min(r, static_cast<int>(n) - 1);
        if (hi <= k) return prefix_xor[r + 1] ^ prefix_xor[l];

        int left_cnt = static_cast<int>(prefix_cnt[l]), right_cnt = static_cast<int>(prefix_cnt[r + 1]);
        return left->lte_xor(left_cnt, right_cnt - 1, k) ^ right->lte_xor(l - left_cnt, r - right_cnt, k);
    }

};

