#include <bits/stdc++.h>
using namespace std;
const int N = 2e6, mod = 1e9 + 7;
using ll = long long;

// Extended Euclidean Algorithm for gcd + coefficients
std::tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
    if (b == 0) return {a, 1, 0};
    ll g, x, y;
    tie(g, x, y) = extended_gcd(b, a % b);
    return {g, y, x - (a / b) * y};
}

array<ll, 3> extend_euclid(ll a, ll b) {
	// we know that (1 * a) + (0 * b) = a and (0 * a) + (1 * b) = b
	array<ll, 3> x = {1, 0, a};
	array<ll, 3> y = {0, 1, b};

	// run extended Euclidean algo
	while (y[2] > 0) {
		// keep subtracting multiple of one equation from the other
		ll k = x[2] / y[2];
		for (int i = 0; i < 3; i++) { x[i] -= k * y[i]; }
		swap(x, y);
	}
	return x;  // x[0] * a + x[1] * b = x[2], x[2] = gcd(a, b)
}