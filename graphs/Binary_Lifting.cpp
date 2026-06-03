#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// Ordered set/map aliases (not used here, but kept from your template)
template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using omset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T, typename R>
using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Pragmas
#pragma GCC optimize("O3,unroll-loops")

// Speed
#define Code ios_base::sync_with_stdio(false);
#define By cin.tie(nullptr);
#define MaraKhaw cout.tie(nullptr);

// Aliases
using ll = long long;
using lld = long double;
using ull = unsigned long long;

// Constants
const lld pi = 3.141592653589793238;
const ll INF = LLONG_MAX;
const ll mod = 1e9 + 7;

// Typedefs
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
#define fl(i, n) for (ll i = 0; i < (n); i++)
#define fls(i, m, n) for (ll i = (m); i <= (n); i++)
#define rl(i, m, n) for (ll i = (n); i >= (m); i--)
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

// Operator overloads
template <typename T1, typename T2>
istream &operator>>(istream &istream, pair<T1, T2> &p)
{
    return (istream >> p.first >> p.second);
}
template <typename T>
istream &operator>>(istream &istream, vector<T> &v)
{
    for (auto &it : v)
        istream >> it;
    return istream;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &ostream, const pair<T1, T2> &p)
{
    return (ostream << p.first << " " << p.second);
}
template <typename T>
ostream &operator<<(ostream &ostream, const vector<T> &c)
{
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}

#define print(x) cout << x << '\n'

mt19937 rng;
int getRandomNumber(int l, int r)
{
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

void preSolve()
{
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
}

// ----------------- LCA CODE STARTS HERE -----------------

#define int ll      // your original style (so vector<int> = vector<long long>)
vector<vll> adj;
ll n;
int LG;            // maximum power of 2 for binary lifting

int timer = 0;
vector<int> tin, tout, dep;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;

    for (int i = 1; i <= LG; ++i)
        up[v][i] = up[ up[v][i - 1] ][i - 1];

    for (int u : adj[v])
    {
        if (u != p)
        {
            dep[u] = dep[v] + 1;
            dfs(u, v);
        }
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;

    for (int i = LG; i >= 0; --i)
    {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root)
{
    tin.assign(n, 0);
    tout.assign(n, 0);
    dep.assign(n, 0);
    timer = 0;
    LG = (int)ceil(log2((long double)n));
    up.assign(n, vector<int>(LG + 1));
    dfs(root, root);
}

int dist(int u, int v)
{
    int w = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[w];
}

int kth_ancestor(int node, int k)
{
    if (dep[node] < k)
        return -1;
    for (int i = 0; i <= LG; ++i)
        if (k & (1LL << i))
            node = up[node][i];
    return node;
}

// kth node on path from u to v (0-based: k=0 -> u)
int kth_node_from_u_to_v(int u, int v, int k)
{
    int w = lca(u, v);
    int dist_u_to_w = dep[u] - dep[w];
    if (k <= dist_u_to_w)
        return kth_ancestor(u, k);
    k -= dist_u_to_w;
    int dist_w_to_v = dep[v] - dep[w];
    // from w to v we move (dist_w_to_v - k) upwards from v
    return kth_ancestor(v, dist_w_to_v - k);
}

// ----------------- SOLVE -----------------

void solve()
{
    ll q;
    cin >> n >> q;

    adj.assign(n, vll());  // clear & resize adjacency list

    // Tree given as parent of node i (1-based in input), root = 1
    // We use 0-based indexing internally.
    fls(i, 1, n - 1)
    {
        ll x;
        cin >> x;
        x--;          // parent index (0-based)
        adj[i].pb(x); // edge child i -> parent x
        adj[x].pb(i); // undirected edge
    }

    preprocess(0); // root is node 0 (original node 1)

    fl(i, q)
    {
        ll x, y;
        cin >> x >> y;
        x--, y--;
        print(lca(x, y) + 1); // convert back to 1-based
    }
}

signed main()
{
    Code By MaraKhaw
    preSolve();
    ll t = 1;
    // cin >> t;
    fl(i, t)
    {
        solve();
    }
    return 0;
}
