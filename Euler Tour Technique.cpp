#include <iostream>
#include <bits/stdc++.h>
// #include <sys/resource.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace chrono;
using namespace __gnu_pbds;
template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using omset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Pragmas
#pragma GCC optimize("O3,unroll-loops")
// #ifndef LOCAL_PROJECT
// #pragma GCC target("avx2")
// #endif
// #pragma GCC optimize("Ofast")

// Speed
#define Code ios_base::sync_with_stdio(false);
#define By cin.tie(NULL);
#define MaraKhaw cout.tie(NULL);

// Aliases
using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const lld pi = 3.141592653589793238;
const ll INF = LONG_LONG_MAX;
const ll mod = 1e9 + 7;

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;

// Macros
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define fl(i, n) for (ll i = 0; i < n; i++)
#define fls(i, m, n) for (ll i = m; i <= n; i++)
#define rl(i, m, n) for (ll i = n; i >= m; i--)
#define py cout << "YES\n";
#define pm cout << "-1\n";
#define pn cout << "NO\n";
#define vr(v) v.begin(), v.end()
#define rv(v) v.rbegin(), v.rend()
#define edl '\n'
#define len(v) v.size()
#define nl cout << edl;

// Debug
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '"' << x << '"'; }
void __print(const string &x) { cerr << '"' << x << '"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif
template <typename T>
ostream &operator+(ostream &o, const vector<T> &v)
{
    for (const auto &x : v)
    {
        o << x << " ";
    }
    o << "\n";
    return o;
}
template <typename T>
ostream &operator*(ostream &o, const vector<T> &v)
{
    for (const auto &x : v)
    {
        o + x;
    }
    return o;
}

// Custom hash map
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template <typename T1, typename T2> // Key should be integer type
using safe_map = unordered_map<T1, T2, custom_hash>;

// Operator overloads
template <typename T1, typename T2> // cin >> pair<T1, T2>
istream &operator>>(istream &istream, pair<T1, T2> &p)
{
    return (istream >> p.first >> p.second);
}
template <typename T> // cin >> vector<T>
istream &operator>>(istream &istream, vector<T> &v)
{
    for (auto &it : v)
        cin >> it;
    return istream;
}
template <typename T1, typename T2> // cout << pair<T1, T2>
ostream &operator<<(ostream &ostream, const pair<T1, T2> &p)
{
    return (ostream << p.first << " " << p.second);
}
template <typename T> // cout << vector<T>
ostream &operator<<(ostream &ostream, const vector<T> &c)
{
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}

// Utility functions
#define print(x) cout << x << '\n'

// template <typename T, typename... Args>
// void print(T &&t, Args &&...args)
// {
//     cout << t << " ";
//     print(forward<Args>(args)...);
// }

template <typename T>
int32_t size_i(T &container) { return static_cast<int32_t>(container.size()); }

void printarr(ll arr[], ll n)
{
    fl(i, n) cout << arr[i] << " ";
    cout << "\n";
}
template <typename T>
void printvec(vector<T> v)
{
    ll n = v.size();
    fl(i, n) cout << v[i] << " ";
    cout << "\n";
}

template <typename T>
ll sumvec(vector<T> v)
{
    ll n = v.size();
    ll s = 0;
    fl(i, n) s += v[i];
    return s;
}

// Mathematical functions
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
} //__gcd

int GCD_extended(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1)
    {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

ll lcm(ll a, ll b) { return (a / gcd(a, b) * b); }
ll moduloMultiplication(ll a, ll b, ll mod) // (a * b) % mod
{
    ll res = 0; // Initialize result
    a %= mod;   // Update a if it is more than or equal to mod

    while (b)
    {
        // If b is odd, add 'a' to result
        if (b & 1)
            res = (res + a) % mod;

        // Here we ensure 'a' does not overflow by doubling it and taking modulo
        a = (a * 2) % mod;

        // Right shift b by 1
        b >>= 1;
    }
    return res;
}

ll modpow(ll x, ll n, int m = mod)
{
    if (x == 0 && n == 0)
        return 0; // undefined case
    ll res = 1;
    while (n > 0)
    {
        if (n % 2)
            res = (res * x) % m;
        x = (x * x) % m;
        n /= 2;
    }
    return res;
}

int modinv(int x, int m = mod)
{
    return modpow(x, m - 2, m);
}
mt19937 rng;
int getRandomNumber(int l, int r)
{
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

// Sorting
bool sorta(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}
bool sortd(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second > b.second;
    return a.first > b.first;
}

bool sortad(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}

bool sortda(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first > b.first;
}

// Bits
string decToBinary(int n)
{
    string s = "";
    int i = 0;
    while (n > 0)
    {
        s = to_string(n % 2) + s;
        n = n / 2;
        i++;
    }
    return s;
}
ll binaryToDecimal(string n)
{
    string num = n;
    ll dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}

// Check
bool isPrime(ll n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
bool isPowerOfTwo(int n)
{
    if (n == 0)
        return false;
    return (ceil(log2(n)) == floor(log2(n)));
}
bool isPerfectSquare(ll x)
{
    if (x >= 0)
    {
        ll sr = sqrt(x);
        return (sr * sr == x);
    }
    return false;
}

// void allocateStackMax()
// {
//     rlimit R;
//     getrlimit(RLIMIT_STACK, &R);
//     R.rlim_cur = R.rlim_max;
//     setrlimit(RLIMIT_STACK, &R);
// }

void preSolve()
{
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    // allocateStackMax();
}

ll mex1(vll v)
{
    ll n = v.size();
    sort(vr(v));
    if (v[0] != 0)
        return 0;
    fl(i, n - 1)
    {
        if (v[i + 1] - v[i] > 1)
            return v[i] + 1;
    }
    return v[n - 1] + 1;
}

ll mex2(vll v)
{
    sort(vr(v));
    ll mx = 0;
    fl(i, v.size())
    {
        if (v[i] == mx)
        {
            mx++;
        }
    }
    return mx;
}

// Comparator for the priority_queue
struct Compare
{
    bool operator()(const pll &a, const pll &b)
    {
        // First sort by the first element in descending order
        if (a.first != b.first)
            return a.first < b.first;
        // If first elements are equal, sort by the second element in ascending order
        return a.second > b.second;
    }
};

ll n, m, tim = 0;
vll v;
vll start, finish;
vector<vll> adj;

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

ll combine_query(ll a, ll b) { return a + b; };
ll combine_updates(ll up1, ll up2) { return up1 + up2; };
ll apply_update(ll node_val, ll update_val, ll len)
{
    return node_val + update_val * len;
};

vll arr(2e5 + 10, 0);
SegmentTree<ll, ll> st(
            arr.size(),
            0, 0,
            combine_query, combine_updates, apply_update,
            arr);

void dfs(ll node, ll p = -1)
{
    start[node] = ++tim;
    st.range_update(start[node], start[node] + 1, v[node]);
    for (auto u : adj[node])
    {
        if (u == p)
            continue;
        dfs(u, node);
    }
    finish[node] = tim;
}

// Code
void solve()
{
    cin >> n >> m;
    v.resize(n);
    start.resize(n);
    finish.resize(n);
    adj.resize(n);
    cin >> v;

    fl(i, n - 1)
    {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // Initialize st with appropriate parameters

    dfs(0); // Perform DFS to set up start and finish times

    fl(i, m)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            ll s, x;
            cin >> s >> x;
            s--;
            st.range_update(start[s], start[s] + 1, -v[s]);
            v[s] = x;
            st.range_update(start[s], start[s] + 1, v[s]);
        }
        else
        {
            ll s;
            cin >> s;
            s--;
            cout << st.query(start[s], finish[s] + 1) << edl;
        }

        // for(auto j:st.tree)
        // {
        //     cout<<j<<" ";
        // }
        // nl;
    }
}

// Main
signed main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("Error.txt", "w", stderr);
    // #endif
    Code By MaraKhaw
    preSolve();
    ll t = 1;
    // cin >> t;
    fl(i, t)
    {
        solve();
    }
    // solve();
    // fl(i,t) //Kickstart
    // {
    //     cout<<"Case #"<<i+1<<": ";
    //     solve();
    //     cout<<"\n";
    // }
    return 0;
}
