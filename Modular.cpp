#include <bits/stdc++.h>
using namespace std;
const int N = 2e6, mod = 1e9 + 7;

template <const int32_t MOD>
struct modint
{
    int32_t value;
    modint() = default;
    modint(int64_t value_)
    {
        value = int32_t(value_ % MOD);
        if (value < 0)
            value += MOD;
    }
    inline modint<MOD> operator+(modint<MOD> other) const
    {
        int32_t c = this->value + other.value;
        return modint<MOD>(c >= MOD ? c - MOD : c);
    }
    inline modint<MOD> operator-(modint<MOD> other) const
    {
        int32_t c = this->value - other.value;
        return modint<MOD>(c < 0 ? c + MOD : c);
    }
    inline modint<MOD> operator*(modint<MOD> other) const
    {
        int32_t c = (int64_t)this->value * other.value % MOD;
        return modint<MOD>(c < 0 ? c + MOD : c);
    }
    inline modint<MOD> &operator+=(modint<MOD> other)
    {
        this->value += other.value;
        if (this->value >= MOD)
            this->value -= MOD;
        return *this;
    }
    inline modint<MOD> &operator-=(modint<MOD> other)
    {
        this->value -= other.value;
        if (this->value < 0)
            this->value += MOD;
        return *this;
    }
    inline modint<MOD> &operator*=(modint<MOD> other)
    {
        this->value = (int64_t)this->value * other.value % MOD;
        if (this->value < 0)
            this->value += MOD;
        return *this;
    }
    inline modint<MOD> operator-() const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const
    {
        modint<MOD> x = *this, y = 1;
        for (; k; k >>= 1)
        {
            if (k & 1)
                y *= x;
            x *= x;
        }
        return y;
    }
    modint<MOD> inv() const { return pow(MOD - 2); } // MOD must be a prime
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
    inline bool operator==(modint<MOD> other) const { return value == other.value; }
    inline bool operator!=(modint<MOD> other) const { return value != other.value; }
    inline bool operator<(modint<MOD> other) const { return value < other.value; }
    inline bool operator>(modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD>
modint<MOD> operator*(int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD>
modint<MOD> operator*(int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD>
istream &operator>>(istream &in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

struct Combi
{
    int n;
    vector<mint> facts, finvs, invs;
    Combi(int _n) : n(_n), facts(_n), finvs(_n), invs(_n)
    {
        facts[0] = finvs[0] = 1;
        invs[1] = 1;
        for (int i = 2; i < n; i++)
            invs[i] = invs[mod % i] * (-mod / i);
        for (int i = 1; i < n; i++)
        {
            facts[i] = facts[i - 1] * i;
            finvs[i] = finvs[i - 1] * invs[i];
        }
    }
    inline mint fact(int n) { return facts[n]; }
    inline mint finv(int n) { return finvs[n]; }
    inline mint inv(int n) { return invs[n]; }
    inline mint ncr(int n, int k) { return (n < k or n < 0 or k < 0) ? 0 : facts[n] * finvs[k] * finvs[n - k]; }
};
Combi C(N);

mint yo(int n, int win)
{
    if (n == 2)
    {
        if (win)
            return 1;
        return 0;
    }
    mint ans = 0;
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
    // 1. Basic Modular Arithmetic
    mint a = 10, b = 3;
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
