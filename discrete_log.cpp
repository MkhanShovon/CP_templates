#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

// --- Type aliases ---
using ll = long long;


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int discrete_log(int a, int b, ll p) {
    a %= p, b %= p;
    if(a == 0){
        if(b == 1){
            return 0;
        }
        else if(b == 0){
            return 1;
        }
        else{
            return -1;
        }
    }
    if(b == 1 || p == 1) return 0;

    gp_hash_table<ll, ll> mp;
    int cnt = 0;
    long long sum = 1;

    for(int g = gcd(a, p); g != 1; g = gcd(a, p)) {
        if(b % g) return -1;
        p /= g, b /= g;
        sum = sum * (a / g) % p;
        cnt++;
        if(sum == b) return cnt;
    }

    int m = (int)ceil(sqrt((double)p));
    long long base = b;
    for(int i = 0; i < m; i++) {
        mp[base] = i;
        base = base * a % p;
    }

    long long step = 1;
    for(int i = 0; i < m; i++) step = step * a % p;

    long long cur = sum;
    for(int i = 1; i <= m+1; i++) {
        cur = cur * step % p;
        if(mp.find(cur) != mp.end())
            return i * m - mp[cur] + cnt;
    }
    return -1;
}

// --- Example usage ---
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b, m;
    cin >> a >> b >> m;

    ll x = discrete_log(a, b, m);
    if (x == -1) cout << "No solution\n";
    else cout << x << "\n";

    return 0;
}
