#include <bits/stdc++.h>
using namespace std;

const int N = 2e6;
int mod = 1000000007; // set mod BEFORE any combinatorics

struct modint {
    int32_t value;
    modint() : value(0) {}
    modint(long long v) {
        v %= mod;
        if (v < 0) v += mod;
        value = (int32_t)v;
    }
    inline modint operator+(modint o) const {
        int32_t c = value + o.value;
        if (c >= mod) c -= mod;
        return modint(c);
    }
    inline modint operator-(modint o) const {
        int32_t c = value - o.value;
        if (c < 0) c += mod;
        return modint(c);
    }
    inline modint operator*(modint o) const {
        return modint(1LL * value * o.value % mod);
    }
    inline modint& operator+=(modint o){ return *this = *this + o; }
    inline modint& operator-=(modint o){ return *this = *this - o; }
    inline modint& operator*=(modint o){ return *this = *this * o; }
    inline modint operator-() const { return modint(value ? mod - value : 0); }
    modint pow(uint64_t k) const {
        modint x = *this, y = 1;
        while (k) { if (k & 1) y *= x; x *= x; k >>= 1; }
        return y;
    }
    modint inv() const { return pow(mod - 2); } // mod must be prime
    inline modint operator/(modint o) const { return *this * o.inv(); }
    inline modint& operator/=(modint o){ return *this *= o.inv(); }
};
ostream& operator<<(ostream& out, modint n){ return out << n.value; }

using mint = modint;

struct Combi {
    int n;
    vector<mint> fact_, finv_, inv_;
    Combi(int _n) : n(_n), fact_(_n), finv_(_n), inv_(_n) {
        fact_[0] = finv_[0] = 1;
        inv_[0] = 0;            // unused, but set to be safe
        if (n > 1) inv_[1] = 1;
        for (int i = 2; i < n; i++) {
            // inv[i] = (mod - mod/i) * inv[mod % i] % mod
            inv_[i] = mint(mod - mod / i) * inv_[mod % i];
        }
        for (int i = 1; i < n; i++) {
            fact_[i] = fact_[i - 1] * mint(i);
            finv_[i] = (i == 1) ? 1 : finv_[i - 1] * inv_[i];
        }
    }
    inline mint fact(int k)  const { return fact_[k]; }
    inline mint finv(int k)  const { return finv_[k]; }
    inline mint inv(int k)   const { return inv_[k]; }
    inline mint ncr(int nn, int kk) const {
        if (kk < 0 || nn < 0 || kk > nn) return mint(0);
        return fact_[nn] * finv_[kk] * finv_[nn - kk];
    }
};

// construct AFTER mod is set (here it's already set globally)
Combi C(N);

mint yo(int n, int win) {
    if (n == 2) return win ? mint(1) : mint(0);
    mint ans = 0;
    if (win) {
        ans = C.ncr(n - 1, n / 2 - 1);
        ans += yo(n - 2, !win);
    } else {
        ans = C.ncr(n - 2, n / 2 - 2);
        ans += yo(n - 2, !win);
    }
    return ans;
}

int main() {
    // Basic Modular Arithmetic
    mint a = 10, b = 3;
    cout << "a + b = " << a + b << "\n";
    cout << "a - b = " << a - b << "\n";
    cout << "a * b = " << a * b << "\n";
    cout << "a / b = " << a / b << "\n";

    // Modular Exponentiation
    cout << "a^3 = " << a.pow(3) << "\n";

    // Modular Inverse
    cout << "a^-1 = " << a.inv() << "\n";

    // Combinatorics Calculations
    int n = 5, r = 2;
    cout << "n! = " << C.fact(n) << "\n";
    cout << "n!^-1 = " << C.finv(n) << "\n";
    cout << "nCr = " << C.ncr(n, r) << "\n";

    // Paths in a Grid
    int grid_n = 4, grid_m = 3;
    cout << "Paths in a grid: " << C.ncr(grid_n + grid_m - 2, grid_n - 1) << "\n";
}
