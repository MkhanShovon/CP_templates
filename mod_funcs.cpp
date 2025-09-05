#include <bits/stdc++.h>
using namespace std;
const int N = 2e6, mod = 1e9 + 7;
using ll = long long;


// Modular multiplication: (a * b) % mod without overflow
ll moduloMultiplication(ll a, ll b, ll mod) {
    ll res = 0;
    a %= mod;  
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

// Modular exponentiation: (x^n) % m
ll modpow(ll x, ll n, int m = mod) {
    if (x == 0 && n == 0) return 1; // undefined case
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = (res * x) % m;
        x = (x * x) % m;
        n /= 2;
    }
    return res;
}

// Modular inverse using Fermat's Little Theorem (works if m is prime)
int modinv(int x, int m = mod) {
    return modpow(x, m - 2, m);
}

// Extended Euclidean Algorithm for gcd + coefficients
std::tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
    if (b == 0) return {a, 1, 0};
    ll g, x, y;
    tie(g, x, y) = extended_gcd(b, a % b);
    return {g, y, x - (a / b) * y};
}

// Modular inverse using Extended Euclid (works for any m if gcd(b, m) == 1)
long long mod_inverse(long long b, long long n) {
    long long g, x, y;
    tie(g, x, y) = extended_gcd(b, n);
    if (g != 1) throw std::invalid_argument("Inverse does not exist.");
    return (x % n + n) % n;
}

// Modular division: (a / b) % n
long long mod_division(long long a, long long b, long long n) {
    long long g = gcd(b, n);
    if (a % g != 0) throw std::invalid_argument("No solution exists.");
    a /= g; b /= g; n /= g;
    long long b_inv = mod_inverse(b, n);
    return (a * b_inv) % n;
}
