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

template <typename T, typename R>
using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Pragmas
#pragma GCC optimize("O3,unroll-loops")
// #ifndef LOCAL_PROJECT
// #pragma GCC target("avx2")
// #endif
// #pragma GCC optimize("Ofast")

// Speed
inline void FastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// Aliases
using ll = long long;
using lld = long double;
using ull = unsigned long long;
using i128 = __int128_t;


// Constants
const lld pi = 3.141592653589793238;
const ll INF = 1e16;

// TypeDEf
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef unordered_map<ll, ll> umll;
typedef map<ll, ll> mll;
typedef priority_queue<int, vector<int>, greater<int>> minHeap;

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

template <typename T>
ll sumvec(vector<T> v)
{
    ll n = v.size();
    ll s = 0;
    fl(i, n) s += v[i];
    return s;
}

long long rng()
{
    static std::mt19937 gen(
        std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}

void preSolve()
{
    // rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    // allocateStackMax();
}

void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) { if (c + 1 < val_range) ++l[c + 1]; ++r[c]; }
    partial_sum(l.begin(), l.end(), l.begin()); partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA) if (i >= 1 && sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1; // Sort L-types
    fill(r.begin(), r.end(), 0); for (int c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k]) 
        if (i >= 1 && !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1; // Sort S-types
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
    const int n = vec.size(); vector<int> SA(n), lms_idx; vector<bool> sl(n); sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) { // Classify types & find LMS nodes
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end()); induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i) if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
    int cur = 0; SA[n - 1] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) { // Rename LMS substrings
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) { SA[j] = ++cur; continue; }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) { flag = true; break; }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) { flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1])); break; }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for (size_t i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < (int)lms_idx.size()) { // Recursive call if not unique
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for (size_t i = 0; i < lms_idx.size(); ++i) new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx); return SA;
}

struct SuffixArray {
    string s; int n;
    vector<int> p, pos, lcp, lg; vector<vector<int>> st;
    SuffixArray(string text, char sentinel = ' ') {
        s = text + sentinel; n = s.size(); pos.assign(n, 0); lcp.assign(n, 0);
        vector<int> vec(n); for (int i = 0; i < n; i++) vec[i] = s[i];
        p = SA_IS(vec, 256); // 1. Build SA in O(N)
        for (int i = 0; i < n; i++) pos[p[i]] = i;
        for (int i = 0, k = 0; i < n; i++) { // 2. Build LCP (Kasai) in O(N)
            if (pos[i] == 0) { k = 0; continue; }
            int j = p[pos[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[pos[i] - 1] = k; k = max(0, k - 1);
        }
        lg.assign(n + 1, 0); for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        st.assign(n + 1, vector<int>(20, 0)); for (int i = 0; i < n - 1; i++) st[i][0] = lcp[i];
        for (int j = 1; j < 20; j++) for (int i = 0; i + (1 << j) <= n - 1; i++) // 3. Build RMQ in O(N log N)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) { // Min LCP in range [l, r]
        if (l > r) return 0;
        int k = lg[r - l + 1]; return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) { // LCP of suffixes starting at i and j in O(1)
        if (i == j) return n - i;
        int l = pos[i], r = pos[j]; if (l > r) swap(l, r); return query(l, r - 1);
    }
    bool comp_sub(int l1, int r1, int l2, int r2) { // Lexicographical compare O(1)
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1, c = min({get_lcp(l1, l2), len1, len2});
        return (c < len1 && c < len2) ? s[l1 + c] < s[l2 + c] : len1 < len2;
    }
    pair<int, int> find_pat(const string& pat) { // Find SA range of pattern O(|P| log N)
        int m = pat.size(), l = 0, r = n - 1, f = -1, lst = -1;
        while (l <= r) { // Lower bound
            int mid = l + (r - l) / 2;
            if (s.compare(p[mid], m, pat) >= 0) f = mid, r = mid - 1; else l = mid + 1;
        }
        if (f == -1 || s.compare(p[f], m, pat) != 0) return {-1, -1};
        l = 0, r = n - 1;
        while (l <= r) { // Upper bound
            int mid = l + (r - l) / 2;
            if (s.compare(p[mid], m, pat) <= 0) lst = mid, l = mid + 1; else r = mid - 1;
        }
        return {f, lst};
    }
    int count_pat(const string& pat) { // Frequency of external pattern
        auto r = find_pat(pat); return r.first == -1 ? 0 : r.second - r.first + 1;
    }
    pair<int, int> find_occ(int idx, int len) { // SA range of internal substring O(log N)
        int rnk = pos[idx], l = 0, r = rnk - 1; pair<int, int> ans = {rnk, rnk};
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(mid, rnk - 1) >= len) ans.first = mid, r = mid - 1; else l = mid + 1;
        }
        l = rnk + 1, r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (query(rnk, mid - 1) >= len) ans.second = mid, l = mid + 1; else r = mid - 1;
        }
        return ans;
    }
};

// Code
void solve()
{
    ll n;
    cin >> n;
    string s;
    fl(i, n)
    {
        char c;
        cin >> c;
        s.pb(c);
    }
    
    string w = s + s;
    SuffixArray sa(w);
    ll best = 0;
    fls(k, 1, n - 1)
    {
        ll l = sa.get_lcp(best, k);
        if(l < n)
        {
            ll vb = (s[l] - '0') ^ (w[best + l] - '0');
            ll vc = (s[l] - '0') ^ (w[k + l] - '0');

            if(vb < vc)
            {
                best = k;
            }
        }
    }

    fl(i, n)
    {
        cout << ((s[i] - '0') ^ (w[i + best] - '0')) << " ";
    }
    nl;
}
// Main
signed main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("Error.txt", "w", stderr);
    // #endif
    FastIO();
    preSolve();
    ll t = 1;
    cin >> t;
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
// End
