#include <bits/stdc++.h>
using namespace std;
const int N = 2e6, mod = 1e9 + 7;
using ll = long long;

// Extended Euclidean Algorithm for gcd + coefficients
std::tuple<ll, ll, ll> extended_gcd(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    ll g, x, y;
    tie(g, x, y) = extended_gcd(b, a % b);
    return {g, y, x - (a / b) * y};
}

long long mod_inv(long long b, long long n) {
    long long g, x, y;
    tie(g, x, y) = extended_gcd(b, n);
    if (g != 1) throw std::invalid_argument("Inverse does not exist.");
    return (x % n + n) % n;
}

struct Congruence {
    long long a, m;
};

long long crt(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto &c : congruences) M *= c.m;

    long long res = 0;
    for (auto &c : congruences) {
        long long Mi = M / c.m;
        long long Ni = mod_inv(Mi, c.m); // modular inverse
        res = (res + c.a * Mi % M * Ni) % M;
    }
    return res;
}
