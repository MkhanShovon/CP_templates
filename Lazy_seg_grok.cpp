#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
struct SegmentTree {
private:
    size_t n; // Size of the segment tree (power of 2)
    std::vector<T> tree; // Tree storage for combined values
    std::vector<T> lazy; // Lazy storage for pending updates
    T neutral_value; // Neutral value for the operation (e.g., 0 for sum)
    std::function<T(T, T)> combine; // Function to combine two segments

    // Apply the lazy update to a node and propagate to children
    void propagate(ll x, ll lx, ll rx) {
        if (lazy[x] == neutral_value) return; // No pending update
        tree[x] = tree[x] + lazy[x] * (rx - lx); // Apply update to current node (for sum)
        if (rx - lx > 1) { // Not a leaf, propagate to children
            lazy[2 * x + 1] = lazy[2 * x + 1] + lazy[x];
            lazy[2 * x + 2] = lazy[2 * x + 2] + lazy[x];
        }
        lazy[x] = neutral_value; // Clear lazy value
    }

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
        propagate(x, lx, rx); // Apply any pending updates
        if (lx >= r || l >= rx) return neutral_value;
        if (lx >= l && rx <= r) return tree[x];
        ll m = (lx + rx) / 2;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return combine(s1, s2);
    }

    void update(ll i, T v, ll x, ll lx, ll rx) {
        propagate(x, lx, rx); // Apply any pending updates
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

    void range_update(ll l, ll r, T v, ll x, ll lx, ll rx) {
        propagate(x, lx, rx); // Apply any pending updates
        if (lx >= r || l >= rx) return;
        if (lx >= l && rx <= r) {
            lazy[x] = lazy[x] + v; // Store update in lazy array
            propagate(x, lx, rx); // Apply immediately to current node
            return;
        }
        ll m = (lx + rx) / 2;
        range_update(l, r, v, 2 * x + 1, lx, m);
        range_update(l, r, v, 2 * x + 2, m, rx);
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
    // For range updates, assumes additive updates (e.g., adding v to a range for sum queries)
    void init(size_t size, T neutral, std::function<T(T, T)> comb) {
        if (size == 0) throw std::invalid_argument("Size must be positive");
        if (!comb) throw std::invalid_argument("Combine function must be provided");
        n = 1;
        while (n < size) n *= 2;
        neutral_value = neutral;
        combine = comb;
        tree.assign(2 * n, neutral_value);
        lazy.assign(2 * n, neutral_value); // Initialize lazy array
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

    // Update the value at position pos to new_val (point update)
    void update(size_t pos, T new_val) {
        if (pos >= n) throw std::invalid_argument("Invalid update position");
        update(pos, new_val, 0, 0, n);
    }

    // Add value v to all elements in range [l, r)
    void range_update(size_t l, size_t r, T v) {
        if (l >= n || r > n || l >= r) throw std::invalid_argument("Invalid range update range");
        range_update(l, r, v, 0, 0, n);
    }
};

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree<int> segTree(arr.size(), 0, [](int a, int b) { return a + b; }, arr);
    std::cout << segTree.query(1, 4) << std::endl; // Outputs 9 (2 + 3 + 4)
    segTree.range_update(1, 4, 2); // Add 2 to arr[1..3]
    std::cout << segTree.query(1, 4) << std::endl; // Outputs 15 (4 + 5 + 6)
    segTree.update(2, 10); // Set arr[2] to 10
    std::cout << segTree.query(1, 4) << std::endl; // Outputs 18 (4 + 10 + 4)
    return 0;
}
