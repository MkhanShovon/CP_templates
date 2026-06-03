#include <bits/stdc++.h>    
using namespace std;

using ll = long long;

template <typename T>
struct SegmentTree {
private:
    size_t n; // Size of the segment tree (power of 2)
    std::vector<T> tree; // Tree storage
    T neutral_value; // Neutral value for the operation (e.g., 0 for sum, INT_MAX for min)
    std::function<T(T, T)> combine; // Function to combine two segments

    void build(const std::vector<T>& a, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            if (lx < static_cast<ll>(a.size())) {
                tree[x] = a[lx];
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    T query(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || l >= rx) return neutral_value;
        if (lx >= l && rx <= r) return tree[x];
        ll m = (lx + rx) / 2;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return combine(s1, s2);
    }

    void update(ll i, T v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);
        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

public:
    // Constructor: Initializes tree with size, neutral value, combine function, and optional array
    SegmentTree(size_t size = 0, T neutral = T(), std::function<T(T, T)> comb = nullptr, const std::vector<T>& arr = {}) {
        if (size > 0) {
            init(size, neutral, comb);
            if (!arr.empty()) build(arr);
        }
    }

    // Initialize the segment tree with size, neutral value, and combine function
    // Combine function must be associative; neutral value must satisfy combine(x, neutral) = x
    void init(size_t size, T neutral, std::function<T(T, T)> comb) {
        if (size == 0) throw std::invalid_argument("Size must be positive");
        if (!comb) throw std::invalid_argument("Combine function must be provided");
        n = 1;
        while (n < size) n *= 2;
        neutral_value = neutral;
        combine = comb;
        tree.assign(2 * n, neutral_value);
    }

    // Build the tree from an input array
    void build(const std::vector<T>& arr) {
        if (arr.size() > n) throw std::invalid_argument("Array size exceeds initialized size");
        build(arr, 0, 0, n);
    }

    // Query the combine operation over range [l, r)
    T query(size_t l, size_t r) {
        if (l >= n || r > n || l >= r) throw std::invalid_argument("Invalid query range");
        return query(l, r, 0, 0, n);
    }

    // Update the value at position pos to new_val
    void update(size_t pos, T new_val) {
        if (pos >= n) throw std::invalid_argument("Invalid update position");
        update(pos, new_val, 0, 0, n);
    }
};

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree<int> segTree(arr.size(), 0, [](int a, int b) { return a + b; }, arr);
    std::cout << segTree.query(1, 4) << std::endl; // Outputs 9 (2 + 3 + 4)
    segTree.update(2, 10); // Update arr[2] to 10
    std::cout << segTree.query(1, 4) << std::endl; // Outputs 16 (2 + 10 + 4)
    return 0;
}