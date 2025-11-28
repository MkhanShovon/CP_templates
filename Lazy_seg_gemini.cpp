#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm> // For std::min
#include <limits>    // For std::numeric_limits
#include <iostream>  // For main function
#include <iomanip>   // For std::setw

// Aliases
using ll = long long;
typedef std::pair<ll, ll> pll;

/**
 * @brief A generic lazy segment tree.
 * * @tparam T The type of the data stored in the tree (query result type).
 * @tparam U The type of the lazy update (update operation type).
 */
template <typename T, typename U>
struct SegmentTree
{
private:
    size_t n;            // Size of the segment tree (power of 2)
    std::vector<T> tree; // Tree storage for combined query values
    std::vector<U> lazy; // Lazy storage for pending updates

    T neutral_query;  // Neutral value for the query operation (e.g., 0 for sum, -inf for max)
    U neutral_update; // Neutral value for the update operation (e.g., 0 for add)

    std::function<T(T, T)> combine_query;    // (T, T) -> T: Combines two query results
    std::function<U(U, U)> combine_updates;  // (U, U) -> U: Combines two pending updates
    std::function<T(T, U, ll)> apply_update; // (T, U, length) -> T: Applies an update to a node

    /**
     * @brief Apply the lazy update to a node and propagate to children.
     */
    void propagate(ll x, ll lx, ll rx)
    {
        if (lazy[x] == neutral_update)
            return; // No pending update

        // Apply the update to the current node
        tree[x] = apply_update(tree[x], lazy[x], rx - lx);

        if (rx - lx > 1)
        { // Not a leaf, propagate to children
            // Combine the current lazy value with children's lazy values
            lazy[2 * x + 1] = combine_updates(lazy[2 * x + 1], lazy[x]);
            lazy[2 * x + 2] = combine_updates(lazy[2 * x + 2], lazy[x]);
        }
        lazy[x] = neutral_update; // Clear lazy value
    }

    /**
     * @brief Build the tree from an initial array.
     * @note This is now generic and builds from std::vector<T>
     */
    void build(const std::vector<T> &a, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < static_cast<ll>(a.size()))
            {
                tree[x] = a[lx]; // Store the value from input array
            }
            else
            {
                // Padding leaves should be neutral
                tree[x] = neutral_query;
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine_query(tree[2 * x + 1], tree[2 * x + 2]);
    }

    /**
     * @brief Perform a range query.
     */
    T query(ll l, ll r, ll x, ll lx, ll rx)
    {
        propagate(x, lx, rx); // Apply any pending updates
        if (lx >= r || l >= rx)
            return neutral_query;
        if (lx >= l && rx <= r)
            return tree[x];
        ll m = (lx + rx) / 2;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return combine_query(s1, s2);
    }

    /**
     * @brief Perform a point update (set value).
     */
    void update(ll i, T v, ll x, ll lx, ll rx)
    {
        propagate(x, lx, rx); // Propagate updates down to the target leaf
        if (rx - lx == 1)
        {
            tree[x] = v; // Set the new value (e.g., {new_k, index})
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m)
        {
            update(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            update(i, v, 2 * x + 2, m, rx);
        }
        // Recalculate parent node value
        tree[x] = combine_query(tree[2 * x + 1], tree[2 * x + 2]);
    }

    /**
     * @brief Perform a range update.
     */
    void range_update(ll l, ll r, U v, ll x, ll lx, ll rx)
    {
        propagate(x, lx, rx); // Apply any pending updates
        if (lx >= r || l >= rx)
            return;
        if (lx >= l && rx <= r)
        {
            lazy[x] = combine_updates(lazy[x], v); // Store update in lazy array
            propagate(x, lx, rx);                  // Apply immediately to current node
            return;
        }
        ll m = (lx + rx) / 2;
        range_update(l, r, v, 2 * x + 1, lx, m);
        range_update(l, r, v, 2 * x + 2, m, rx);
        // Recalculate parent node value from children
        tree[x] = combine_query(tree[2 * x + 1], tree[2 * x + 2]);
    }

public:
    /**
     * @brief Constructor: Initializes tree with parameters and optional array.
     * @note Now generic, builds from std::vector<T>
     */
    SegmentTree(size_t size = 0,
                T n_query = T(),
                U n_update = U(),
                std::function<T(T, T)> c_query = nullptr,
                std::function<U(U, U)> c_updates = nullptr,
                std::function<T(T, U, ll)> a_update = nullptr,
                const std::vector<T> &arr = {}) // Note: Now std::vector<T>
    {
        if (size > 0)
        {
            init(size, n_query, n_update, c_query, c_updates, a_update);
            if (!arr.empty())
                build(arr);
        }
    }

    /**
     * @brief Initialize the segment tree with size and operation functions.
     */
    void init(size_t size,
              T n_query,
              U n_update,
              std::function<T(T, T)> c_query,
              std::function<U(U, U)> c_updates,
              std::function<T(T, U, ll)> a_update)
    {
        if (size == 0)
            throw std::invalid_argument("Size must be positive");
        if (!c_query)
            throw std::invalid_argument("Query combine function must be provided");
        if (!c_updates)
            throw std::invalid_argument("Update combine function must be provided");
        if (!a_update)
            throw std::invalid_argument("Update apply function must be provided");

        n = 1;
        while (n < size)
            n *= 2;

        neutral_query = n_query;
        neutral_update = n_update;
        combine_query = c_query;
        combine_updates = c_updates;
        apply_update = a_update;

        tree.assign(2 * n, neutral_query);
        lazy.assign(2 * n, neutral_update);
    }

    /**
     * @brief Build the tree from an input array.
     */
    void build(const std::vector<T> &arr) // Note: Now std::vector<T>
    {
        if (arr.size() > n)
            throw std::invalid_argument("Array size exceeds initialized size");
        build(arr, 0, 0, n);
    }

    /**
     * @brief Query the combined value over the range [l, r).
     */
    T query(size_t l, size_t r)
    {
        if (l >= n || r > n || l >= r)
            throw std::invalid_argument("Invalid query range");
        return query(l, r, 0, 0, n);
    }

    /**
     * @brief Update the value at position pos to new_val (point set).
     */
    void update(size_t pos, T new_val)
    {
        if (pos >= n)
            throw std::invalid_argument("Invalid update position");
        update(pos, new_val, 0, 0, n);
    }

    /**
     * @brief Apply an update v to all elements in range [l, r).
     */
    void range_update(size_t l, size_t r, U v)
    {
        if (l >= n || r > n || l >= r)
            throw std::invalid_argument("Invalid range update range");
        range_update(l, r, v, 0, 0, n);
    }
};

// --- Main function to demonstrate common use cases ---
int main()
{
    std::cout << "--- Demo 1: Range Add / Range Sum ---" << std::endl;
    {
        using T_Sum = ll;
        using U_Sum = ll;
        std::vector<T_Sum> arr = {1, 2, 3, 4, 5};

        T_Sum neutral_query = 0LL;
        U_Sum neutral_update = 0LL;

        auto combine_query = [](T_Sum a, T_Sum b) { return a + b; };
        auto combine_updates = [](U_Sum up1, U_Sum up2) { return up1 + up2; };
        auto apply_update = [](T_Sum node_val, U_Sum update_val, ll len)
        {
            return node_val + update_val * len;
        };

        SegmentTree<T_Sum, U_Sum> segTree_Sum(
            arr.size(),
            neutral_query, neutral_update,
            combine_query, combine_updates, apply_update,
            arr);

        std::cout << "Initial array: {1, 2, 3, 4, 5}" << std::endl;
        std::cout << "Query [1, 4) (2+3+4): " << segTree_Sum.query(1, 4) << std::endl; // 9

        segTree_Sum.range_update(1, 4, 2); // Add 2 to [1, 4) -> {1, 4, 5, 6, 5}
        std::cout << "After adding 2 to [1, 4)..." << std::endl;
        std::cout << "Query [1, 4) (4+5+6): " << segTree_Sum.query(1, 4) << std::endl; // 15

        segTree_Sum.update(2, 10); // Set index 2 to 10 -> {1, 4, 10, 6, 5}
        std::cout << "After setting index 2 to 10..." << std::endl;
        std::cout << "Query [1, 4) (4+10+6): " << segTree_Sum.query(1, 4) << std::endl; // 20
    }

    std::cout << "\n--- Demo 2: Range Add / Range Min w/ Index ---" << std::endl;
    {
        using T_MinIdx = pll; // {value, index}
        using U_MinIdx = ll;

        std::vector<ll> initial_arr = {5, 2, 3, 1, 4};
        // We must manually create the initial vector of pairs
        std::vector<T_MinIdx> arr;
        for (size_t i = 0; i < initial_arr.size(); ++i)
        {
            arr.push_back({initial_arr[i], (ll)i});
        }

        const ll INF = std::numeric_limits<ll>::max();
        T_MinIdx neutral_query = {INF, -1LL};
        U_MinIdx neutral_update = 0LL;

        auto combine_query = [](T_MinIdx a, T_MinIdx b) { return std::min(a, b); };
        auto combine_updates = [](U_MinIdx up1, U_MinIdx up2) { return up1 + up2; };
        auto apply_update = [](T_MinIdx node_val, U_MinIdx update_val, ll len)
        {
            // length is ignored for Range Add / Range Min
            return T_MinIdx{node_val.first + update_val, node_val.second};
        };

        SegmentTree<T_MinIdx, U_MinIdx> segTree_MinIdx(
            arr.size(),
            neutral_query, neutral_update,
            combine_query, combine_updates, apply_update,
            arr);

        std::cout << "Initial array: {5, 2, 3, 1, 4}" << std::endl;
        pll min_res = segTree_MinIdx.query(0, 5);
        std::cout << "Query [0, 5) (min): val=" << min_res.first << " at idx=" << min_res.second << std::endl; // {1, 3}

        min_res = segTree_MinIdx.query(0, 3);
        std::cout << "Query [0, 3) (min of 5,2,3): val=" << min_res.first << " at idx=" << min_res.second << std::endl; // {2, 1}

        segTree_MinIdx.range_update(0, 5, 10); // Add 10 to all -> {15, 12, 13, 11, 14}
        std::cout << "After adding 10 to [0, 5)..." << std::endl;
        min_res = segTree_MinIdx.query(0, 5);
        std::cout << "Query [0, 5) (min): val=" << min_res.first << " at idx=" << min_res.second << std::endl; // {11, 3}

        segTree_MinIdx.update(3, {0, 3}); // Set index 3 to 0 -> {15, 12, 13, 0, 14}
        std::cout << "After setting index 3 to 0..." << std::endl;
        min_res = segTree_MinIdx.query(0, 5);
        std::cout << "Query [0, 5) (min): val=" << min_res.first << " at idx=" << min_res.second << std::endl; // {0, 3}
    }
    
    std::cout << "\n--- Demo 3: Range Add / Range assign w/ Index ---" << std::endl;
    {
        SegmentTree<ll, ll> st;
        auto c_query = [](ll a, ll b)
        { return (a + b) % MOD; };
        auto c_updates = [](ll a, ll b)
        { return b; };
        auto a_update = [](ll node_val, ll update_val, ll len)
        { return update_val * len % MOD; };
        st.init(n, 0LL, -1LL, c_query, c_updates, a_update);
    }

    return 0;
}
