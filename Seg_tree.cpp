template <typename T>
struct SegmentTree
{
    int n;
    vector<T> tree;
    T neutral_value;           // Neutral value for the operation (e.g., 0 for sum, INT_MAX for min)
    function<T(T, T)> combine; // Function to combine two segments

    void init(int size, T neutral, function<T(T, T)> comb)
    {
        n = 1;
        neutral_value = neutral;
        combine = comb;
        while (n < size)
            n *= 2;
        tree.assign(2 * n, neutral_value);
    }

    void build(const vector<T> &a, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (ll)a.size())
            {
                tree[x] = a[lx];
                // debug(lx,a[lx].mn,a[lx].mx,a[lx].inc);
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    T query(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (lx >= r || l >= rx)
            return neutral_value;
        if (lx >= l && rx <= r)
            return tree[x];
        ll m = (lx + rx) / 2;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return combine(s1, s2);
    }

    void update(ll i, T v, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            tree[x] = v;
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
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    // Helper functions to simplify calling
    void build(const vector<T> &arr)
    {
        build(arr, 0, 0, n);
    }

    T query(int l, int r)
    {
        return query(l, r, 0, 0, n);
    }

    void update(int pos, T new_val)
    {
        update(pos, new_val, 0, 0, n);
    }
};
//SegmentTree<int> segTree(arr.size(), 0, [](int a, int b) { return a + b; });
