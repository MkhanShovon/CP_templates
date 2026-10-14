/*
  WHICH ONE TO USE?
  -------------------------------------------------------------------
  mod is PRIME and n < mod  (most problems, mod = 1e9+7 / 998244353)
      -> 0) Comb      : Comb C(maxN, mod);  C.C(n, r)      O(1) query
  mod is PRIME but n can be >= mod  (small prime mod, huge n)
      -> 1) Lucas     : Lucas L(p);         L.C(n, r)      O(log_p n)
  mod is NOT prime  (142857, 1e6, 2^k, 27, ...)
      -> 2) BinomAnyMod : BinomAnyMod B(m); B.C(n, r)
  -------------------------------------------------------------------
  Build the struct ONCE (outside the test-case loop).
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// ---------- helpers ----------
ll power(ll a, ll e, ll m) {
    a %= m; if (a < 0) a += m;
    ll r = 1 % m;
    while (e) {
        if (e & 1) r = (i128)r * a % m;
        a = (i128)a * a % m;
        e >>= 1;
    }
    return r;
}
// inverse of a mod m, needs gcd(a, m) = 1 (m does NOT need to be prime)
ll inv_mod(ll a, ll m) {
    if (m == 1) return 0;
    a %= m; if (a < 0) a += m;
    ll b = m, u = 1, v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m; if (u < 0) u += m;
    return u;
}

// =====================================================================
// 0) NORMAL TABLE : mod is PRIME and n < mod. n up to ~1e7 (memory).
//    build O(maxN), query O(1). Use this most of the time.
// =====================================================================
struct Comb {
    int mod;
    vector<int> f, inf;
    Comb(int maxN, int mod) : mod(mod), f(maxN + 1), inf(maxN + 1) {
        f[0] = 1;
        for (int i = 1; i <= maxN; i++) f[i] = 1LL * f[i - 1] * i % mod;
        inf[maxN] = power(f[maxN], mod - 2, mod);
        for (int i = maxN; i > 0; i--) inf[i - 1] = 1LL * inf[i] * i % mod;
    }
    ll C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return 1LL * f[n] * inf[r] % mod * inf[n - r] % mod;
    }
};

// =====================================================================
// 1) LUCAS : p is PRIME. n, r up to 1e18. p up to ~1e7 (memory).
//    build O(p), query O(log_p n)
// =====================================================================
struct Lucas {
    int p;
    vector<int> f, inf;
    Lucas(int p) : p(p), f(p), inf(p) {
        f[0] = 1;
        for (int i = 1; i < p; i++) f[i] = 1LL * f[i - 1] * i % p;
        inf[p - 1] = power(f[p - 1], p - 2, p);
        for (int i = p - 1; i > 0; i--) inf[i - 1] = 1LL * inf[i] * i % p;
    }
    ll small(int n, int r) {               // n, r < p
        if (r < 0 || r > n) return 0;
        return 1LL * f[n] * inf[r] % p * inf[n - r] % p;
    }
    ll C(ll n, ll r) {
        if (r < 0 || r > n) return 0;
        ll res = 1;
        while (n || r) {
            res = res * small(n % p, r % p) % p;
            if (res == 0) break;
            n /= p; r /= p;
        }
        return res;
    }
};

// =====================================================================
// 2) ANY MOD m (prime, prime power, or composite like 142857, 1e6...).
//    n, r up to 1e18. Each prime power p^k in m must be <= ~1e7 (memory).
//    build O(sum of p^k) ONCE, query O(sum of p^k-part * log n) -> fast
// =====================================================================
struct BinomAnyMod {
    struct PP { ll p, k, pk; vector<int> f; };
    ll m;
    vector<PP> parts;

    BinomAnyMod(ll m) : m(m) {
        ll x = m;
        for (ll p = 2; p * p <= x; p++) {
            if (x % p) continue;
            ll k = 0, pk = 1;
            while (x % p == 0) x /= p, pk *= p, k++;
            add(p, k, pk);
        }
        if (x > 1) add(x, 1, x);
    }
    void add(ll p, ll k, ll pk) {
        PP q{p, k, pk, vector<int>(pk)};
        q.f[0] = 1;   // f[i] = product of j <= i with p not dividing j, mod p^k
        for (ll i = 1; i < pk; i++)
            q.f[i] = (i % p) ? (ll)q.f[i - 1] * i % pk : q.f[i - 1];
        parts.push_back(move(q));
    }
    static ll vp(ll n, ll p) {   // power of p in n!
        ll c = 0;
        while (n) n /= p, c += n;
        return c;
    }
    ll factmod(ll n, const PP &q) {   // n! without p factors, mod p^k
        ll res = 1;
        while (n > 1) {
            res = res * power(q.f[q.pk - 1], n / q.pk, q.pk) % q.pk;
            res = res * q.f[n % q.pk] % q.pk;
            n /= q.p;
        }
        return res % q.pk;
    }
    ll C_pk(ll n, ll r, const PP &q) {
        ll t = vp(n, q.p) - vp(r, q.p) - vp(n - r, q.p);
        if (t >= q.k) return 0;
        ll res = factmod(n, q);
        res = res * inv_mod(factmod(r, q), q.pk) % q.pk;
        res = res * inv_mod(factmod(n - r, q), q.pk) % q.pk;
        res = res * power(q.p, t, q.pk) % q.pk;
        return res;
    }
    ll C(ll n, ll r) {
        if (r < 0 || r > n || m == 1) return 0;
        ll ans = 0, M = 1;              // CRT: join answers of each p^k
        for (auto &q : parts) {
            ll a = C_pk(n, r, q);
            ll d = ((a - ans) % q.pk + q.pk) % q.pk;
            ll t = (i128)d * inv_mod(M % q.pk, q.pk) % q.pk;
            ans += M * t;
            M *= q.pk;
        }
        return ans;
    }
};

// ---------- example usage ----------
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Normal table (prime mod, n < mod)
    Comb Cb(1000000, 1000000007);
    cout << Cb.C(1000000, 500000) << '\n';

    // Lucas (prime mod, huge n)
    Lucas L(1000003);
    cout << L.C(1000000000LL, 500000) << '\n';

    // Any mod
    BinomAnyMod B(142857);              // 142857 = 3^3 * 11 * 13 * 37
    cout << B.C(1000000000LL, 2) << '\n';

    // Typical: t queries, same mod -> build ONCE outside the loop
    // int t; cin >> t;
    // BinomAnyMod B(m);
    // while (t--) { ll n, r; cin >> n >> r; cout << B.C(n, r) << '\n'; }
}
