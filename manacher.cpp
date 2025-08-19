#include <iostream> 
#include <vector> 
#include <random>
#include <chrono>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
  
using namespace std;

// ==============================
// I/O speedups
// ==============================
inline void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// ==============================
// Type aliases
// ==============================
using ll  = long long;
using lld = long double;
using ull = unsigned long long;

// ==============================
// Constants (generic template)
// ==============================
const lld pi  = 3.141592653589793238L;
const ll  INF = LLONG_MAX;
const ll  mod = 1e9 + 7;

// ==============================
// Typedefs (generic template)
// ==============================
using pll  = pair<ll, ll>;
using vll  = vector<ll>;
using vpll = vector<pll>;
using vs   = vector<string>;
using umll = unordered_map<ll, ll>;
using mll  = map<ll, ll>;

// ==============================
// Macros (loop helpers, etc.)
// ==============================
// fl(i, n):          for i = 0..n-1
// fls(i, m, n):     for i = m..n
// rl(i, m, n):      for i = n..m  (descending)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define fl(i, n)        for (ll i = 0; i < (n); i++)
#define fls(i, m, n)    for (ll i = (m); i <= (n); i++)
#define rl(i, m, n)     for (ll i = (n); i >= (m); i--)
#define py cout << "YES\n";
#define pm cout << "-1\n";
#define pn cout << "NO\n";
#define vr(v) (v).begin(), (v).end()
#define rv(v) (v).rbegin(), (v).rend()
#define edl '\n'
#define len(v) (v).size()
#define nl  cout << edl;

// ==============================
// Stream operators (generic template)
// ==============================
template <typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) {
    return (is >> p.first >> p.second);
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& it : v) is >> it;
    return is;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
    return (os << p.first << " " << p.second);
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& c) {
    for (auto& it : c) cout << it << " ";
    return os;
}

// ==============================
// Utilities (generic template)
// ==============================
#define print(x) cout << x << '\n'

template <typename T>
ll sumvec(vector<T> v) {
    ll s = 0;
    fl(i, (ll)v.size()) s += v[i];
    return s;
}

// RNG (unused by the solution; kept as part of template)
mt19937 rng;
int getRandomNumber(int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

void preSolve() {
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
}

// =======================================================
// MANACHER (sentinel version) → radii on transformed t
// t = "#s0#s1#...#s{n-1}#" so all palindromes are odd in t.
// p[i] = radius in t (how far we match around center i).
//
// Time: O(n), Space: O(n)
// =======================================================
vll manacher(const string& s) {
    ll n = (ll)s.size();

    // Build sentinel string t: between every two chars (and ends) put '#'
    // This unifies odd/even palindromes into a single "odd" case on t.
    string t = "#";
    for (char c : s) t += c + string("#");
    ll m = (ll)t.size();  // m = 2*n + 1

    vll p(m, 0);          // p[i] = radius on t (in chars of t)
    ll c = 0, r = 0;      // current rightmost palindrome center c, right boundary r (inclusive)

    fl(i, m) {
        // Mirror index j of i across center c: j = 2*c - i
        ll mirror = 2 * c - i;

        // If i is inside the current rightmost palindrome (i < r),
        // we can seed p[i] using symmetry, capped by the boundary.
        if (i < r) p[i] = min(r - i, p[mirror]);

        // Greedy expansion around i:
        // Try to match the next pair outside the current radius.
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m &&
               t[i - p[i] - 1] == t[i + p[i] + 1]) {
            p[i]++;
        }

        // If this palindrome extends beyond r, update the rightmost window.
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
    return p;
}

// ======================================================================
// Convert Manacher radii → end_counts[j] = # palindromic substrings that
// end at index j in the ORIGINAL string s.
//
// Idea:
//  • For each center i in the transformed t and its radius p[i], map the
//    possible palindromes in s and collect the range of their END indices.
//  • Odd center in t (i odd)  → center on s[cc], ends ∈ [cc, cc + max_h]
//  • Even center in t (i even)→ center between s[ee-1] and s[ee],
//    ends ∈ [ee, ee + num - 1]
//  • We add these ranges to a difference array 'diff' and prefix-sum to get
//    per-position end_counts.
// Time: O(n), Space: O(n)
// ======================================================================
vll get_end_counts(const string& s) {
    ll n = (ll)s.size();
    vll p = manacher(s);           // radii on sentinel string t
    ll m = (ll)p.size();           // m = 2*n + 1

    // Difference array for range adds over end indices 0..n-1.
    // Size n+1 to allow writing diff[R+1] -= 1 safely.
    vll diff(n + 1, 0);

    fl(i, m) {
        if (p[i] == 0) continue;   // even centers often have 0; nothing to add

        if (i % 2 == 1) {
            // ----- ODD center in t → center on a real character in s -----
            // t index: i = 2*cc + 1  ⇒  cc = (i-1)/2
            // In s, for half-length h = 0..max_h, palindrome s[cc-h..cc+h] ends at (cc + h).
            ll cc     = (i - 1) / 2;   // center in s
            ll max_h  = p[i] / 2;      // maximum half-length in s
            ll low    = cc;            // end indices span [cc, cc + max_h]
            ll high   = cc + max_h;

            // (Safety clamps; with correct mapping high should be < n anyway)
            if (high >= n) high = n - 1;
            if (low > high) continue;

            // Range add +1 on [low..high]
            diff[low] += 1;
            if (high + 1 <= n) diff[high + 1] -= 1;

        } else {
            // ----- EVEN center in t → center between two characters in s -----
            // t index: i = 2*ee      ⇒  ee = i/2 is the index of the *right* char of the gap.
            // For half-length h = 1..num, palindrome s[ee-h..ee+h-1] ends at (ee + h - 1).
            ll ee   = i / 2;        // right index of the gap in s
            ll num  = p[i] / 2;     // maximum half-length (number of pairs)
            if (num == 0) continue; // no even palindromes here

            ll low  = ee;               // end indices span [ee, ee + num - 1]
            ll high = ee + num - 1;

            if (high >= n) high = n - 1;
            if (low > high) continue;

            // Range add +1 on [low..high]
            diff[low] += 1;
            if (high + 1 <= n) diff[high + 1] -= 1;
        }
    }

    // Prefix-sum the difference array to get end_counts[j]:
    // end_counts[j] = number of intervals [L,R] covering j.
    vll end_counts(n, 0);
    ll current = 0;
    fl(j, n) {
        current += diff[j];
        end_counts[j] = current;
    }
    return end_counts;
}

// ======================================================================
// Count disjoint palindrome substring pairs.
//
// Definition: (x, y) is counted if both x and y are palindromes and
// they are disjoint: either x ends before y starts or y ends before x starts.
// We count each unordered pair exactly once by enforcing "x entirely left of y".
//
// Method:
//  1) end_counts[i]   = # pal substrings ending at i.
//  2) start_counts[j] = # pal substrings starting at j.
//     We get start_counts by computing end_counts on reverse(s) and mapping:
//       start_counts[k] = end_counts_r[n-1-k]
//     (a substring starting at k in s corresponds to a substring ending at
//      n-1-k in reverse(s).)
//  3) rights[i] = sum_{j=i}^{n-1} start_counts[j]  (suffix sums)
//  4) Answer = sum_{i=0}^{n-2} end_counts[i] * rights[i+1]
//     (choose a split between i and i+1: left pal ends at i, right pal starts > i)
//
// Time: O(n), Space: O(n)
// ======================================================================
ll count_disjoint_pairs(const string& s) {
    ll n = (ll)s.size();
    if (n == 0) return 0;

    // # pal substrings ending at each index in s
    vll end_counts = get_end_counts(s);

    // Build start_counts via reverse(s) trick
    string sr = s;
    reverse(sr.begin(), sr.end());
    vll end_counts_r = get_end_counts(sr);

    vll start_counts(n, 0);
    // Map: start at k in s  <=>  end at (n-1-k) in reverse(s)
    fl(k, n) {
        start_counts[k] = end_counts_r[n - 1 - k];
    }

    // rights[i] = number of pal substrings starting at positions >= i
    vll rights(n + 1, 0);
    rights[n] = 0;
    rl(i, 0, n - 1) {
        rights[i] = rights[i + 1] + start_counts[i];
    }

    // Count pairs with the split between i and i+1:
    // take any left-pal that ends at i and any right-pal that starts at >= i+1
    ll ans = 0;
    fl(i, n - 1) {
        ans += end_counts[i] * rights[i + 1];
    }
    return ans;
}

// ======================================================================
// Solver: reads multiple test cases (one string per line) until EOF.
// Skips blank lines. Prints the count per line.
// ======================================================================
void solve() {
    string s;
    while (getline(cin, s)) {
        if (s.empty()) continue;           // ignore blank lines
        cout << count_disjoint_pairs(s) << '\n';
    }
}

// ======================================================================
// main
// ======================================================================
signed main() {
    FastIO();
    preSolve();

    ll t = 1;   // We read until EOF inside solve(), so t=1 is fine.
    fl(i, t) {
        solve();
    }
    return 0;
}

/*
===========================
Notes & Correctness Summary
===========================

• Manacher (sentinel version) runs in O(n) and gives p[i] = radius at each t-index.
  Mapping to s:
    - i odd  (center on s[cc]) → ends ∈ [cc, cc + floor(p[i]/2)]
    - i even (center between s[ee-1] and s[ee]) → ends ∈ [ee, ee + floor(p[i]/2) - 1]

• get_end_counts(s):
    - Adds +1 over those end-index ranges using a difference array (diff),
      then prefix-sums to get the exact number of pal substrings ending at each index.

• start_counts:
    - Use reverse(s) and the fact that "start at k in s" corresponds to
      "end at n-1-k in reverse(s)".

• Counting disjoint pairs:
    - For each split between i and i+1, multiply:
        (# pal ends at i) * (# pal starts at positions >= i+1)
      Sum over i = 0..n-2.
    - This counts each unordered pair exactly once with the left one before the right one.

• Complexity:
    - Manacher: O(n)
    - Range adds + prefix sum: O(n)
    - Reverse, mapping, suffix sums, final sum: O(n)
    - Total per test: O(n) time, O(n) memory.

• Range of the answer:
    - In worst-case strings like "aaaa...a", the number of palindromic substrings is Θ(n^2),
      and the number of disjoint pairs is Θ(n^3). For n ≤ 1e5, this fits in signed 64-bit
      (since 1e15 < 2^63), so 'long long' is sufficient.
*/
