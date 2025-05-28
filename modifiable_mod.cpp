#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
int mod;

struct modint
{
    int32_t value;
    modint() = default;
    modint(int64_t value_, int32_t MOD)
    {
        value = int32_t(value_ % MOD);
        if (value < 0)
            value += MOD;
    }
    inline modint operator+(modint other) const
    {
        int32_t c = this->value + other.value;
        return modint(c >= mod ? c - mod : c, mod);
    }
    inline modint operator-(modint other) const
    {
        int32_t c = this->value - other.value;
        return modint(c < 0 ? c + mod : c, mod);
    }
    inline modint operator*(modint other) const
    {
        int32_t c = (int64_t)this->value * other.value % mod;
        return modint(c < 0 ? c + mod : c, mod);
    }
    inline modint &operator+=(modint other)
    {
        this->value += other.value;
        if (this->value >= mod)
            this->value -= mod;
        return *this;
    }
    inline modint &operator-=(modint other)
    {
        this->value -= other.value;
        if (this->value < 0)
            this->value += mod;
        return *this;
    }
    inline modint &operator*=(modint other)
    {
        this->value = (int64_t)this->value * other.value % mod;
        if (this->value < 0)
            this->value += mod;
        return *this;
    }
    inline modint operator-() const { return modint(this->value ? mod - this->value : 0, mod); }
    modint pow(uint64_t k) const
    {
        modint x = *this, y = modint(1, mod);
        for (; k; k >>= 1)
        {
            if (k & 1)
                y *= x;
            x *= x;
        }
        return y;
    }
    modint inv() const { return pow(mod - 2); } // MOD must be a prime
    inline modint operator/(modint other) const { return *this * other.inv(); }
    inline modint &operator/=(modint other) { return *this *= other.inv(); }
    inline bool operator==(modint other) const { return value == other.value; }
    inline bool operator!=(modint other) const { return value != other.value; }
    inline bool operator<(modint other) const { return value < other.value; }
    inline bool operator>(modint other) const { return value > other.value; }
};

modint operator*(int64_t value, modint n) { return modint(value, mod) * n; }
modint operator*(int32_t value, modint n) { return modint(value % mod, mod) * n; }
istream &operator>>(istream &in, modint &n) { return in >> n.value; }
ostream &operator<<(ostream &out, modint n) { return out << n.value; }

using mint = modint;

struct Combi
{
    int n;
    vector<mint> facts, finvs, invs;
    Combi(int _n) : n(_n), facts(_n), finvs(_n), invs(_n)
    {
        facts[0] = finvs[0] = mint(1, mod);
        invs[1] = mint(1, mod);
        for (int i = 2; i < n; i++)
            invs[i] = invs[mod % i] * mint(-mod / i, mod);
        for (int i = 1; i < n; i++)
        {
            facts[i] = facts[i - 1] * mint(i, mod);
            finvs[i] = finvs[i - 1] * invs[i];
        }
    }
    inline mint fact(int n) { return facts[n]; }
    inline mint finv(int n) { return finvs[n]; }
    inline mint inv(int n) { return invs[n]; }
    inline mint ncr(int n, int k) { return (n < k or n < 0 or k < 0) ? mint(0, mod) : facts[n] * finvs[k] * finvs[n - k]; }
};
Combi C(N);

mint yo(int n, int win)
{
    if (n == 2)
    {
        if (win)
            return mint(1, mod);
        return mint(0, mod);
    }
    mint ans = mint(0, mod);
    if (win)
    {
        ans = C.ncr(n - 1, n / 2 - 1);
        ans += yo(n - 2, !win);
    }
    else
    {
        ans = C.ncr(n - 2, n / 2 - 2);
        ans += yo(n - 2, !win);
    }
    return ans;
}

int main()
{
    mod = 1e9 + 7;
    // 1. Basic Modular Arithmetic
    mint a = mint(10, mod), b = mint(3, mod);
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;

    // 2. Modular Exponentiation
    cout << "a^3 = " << a.pow(3) << endl;

    // 3. Modular Inverse
    cout << "a^-1 = " << a.inv() << endl;

    // 4. Combinatorics Calculations
    int n = 5, r = 2;
    cout << "n! = " << C.fact(n) << endl;
    cout << "n!^-1 = " << C.finv(n) << endl;
    cout << "nCr = " << C.ncr(n, r) << endl;

    // 5. Paths in a Grid
    int grid_n = 4, grid_m = 3;
    cout << "Paths in a grid: " << C.ncr(grid_n + grid_m - 2, grid_n - 1) << endl;
}