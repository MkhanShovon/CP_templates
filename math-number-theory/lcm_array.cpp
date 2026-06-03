#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

ll lcm_array(const vector<ll>& v, ll limit) {
    i128 L = 1;
    for (ll x : v) {
        ll g = std::gcd((ll)L, x);
        i128 t = (L / g) * (i128)x;
        if (t > (i128)limit) return limit + 1; // cap: larger than limit means useless
        L = t;
    }
    return (ll)L;
}
