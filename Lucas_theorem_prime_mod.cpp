#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static int MOD; // prime
vector<int> fac, inv; // size MOD, indices 0..MOD-1

ll modpow(ll a, ll e) {
    ll r = 1 % MOD;
    a %= MOD;
    if (a < 0) a += MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

void build_fact_inv() {
    fac.assign(MOD, 1);
    for (int i = 1; i < MOD; ++i) fac[i] = (ll)fac[i-1] * i % MOD;
    inv.assign(MOD, 1);
    inv[MOD-1] = (int)modpow(fac[MOD-1], MOD - 2);
    for (int i = MOD-1; i >= 1; --i) inv[i-1] = (ll)inv[i] * i % MOD;
}

inline int nCr_precomp(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (ll)fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}

// multiplicative nCr for a single digit (n, r < MOD), no precompute required
int nCr_small(int n, int r) {
    if (r < 0 || r > n) return 0;
    r = min(r, n - r);
    ll num = 1, den = 1;
    for (int i = 1; i <= r; ++i) {
        num = num * (n - r + i) % MOD;
        den = den * i % MOD;
    }
    return (int)(num * modpow(den, MOD - 2) % MOD);
}

// Lucas using either precomputed factorials or multiplicative per digit
int lucas_ll(ll n, ll r, bool have_precomp) {
    if (r < 0 || r > n) return 0;
    int res = 1;
    while (n > 0 || r > 0) {
        int ni = (int)(n % MOD);
        int ri = (int)(r % MOD);
        if (ri > ni) return 0;
        int term = have_precomp ? nCr_precomp(ni, ri) : nCr_small(ni, ri);
        res = (ll)res * term % MOD;       // <-- MOD taken here
        n /= MOD;
        r /= MOD;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        long long n, r, p;
        cin >> n >> r >> p;
        MOD = (int)p;

        // If MOD is reasonably small, precompute up to MOD-1; else use multiplicative per digit
        bool can_precomp = (MOD > 1) && (MOD <= 2000000); // tune threshold if you like
        if (can_precomp) build_fact_inv();

        cout << lucas_ll(n, r, can_precomp) << '\n';
    }
    return 0;
}
