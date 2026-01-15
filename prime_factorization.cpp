#include<bits/stdc++.h>
using namespace std;    
using ll = long long;
using vpll = vector<pair<ll, ll>> ;

// Function to find all prime factors of a number
vpll factorization(ll n) {
    vpll fac;
    if (n % 2 == 0) {
        ll count = 0;
        while (n % 2 == 0) {
            count++;
            n /= 2;
        }
        fac.push_back({2, count});
    }
    for (long long d = 3; d * d <= n; d += 2) { 
        if (n % d == 0) {
            ll count = 0;
            while (n % d == 0) {
                count++;
                n /= d;
            }
            fac.push_back({d, count});
        }
    }
    if (n > 1) {
        fac.push_back({n, 1});
    }
    return fac;
}

// 2. Sieve-Based Factorization (Fast for Many Queries)
// O(n log log n) for preprocessing, O(log n) for each query
const int N = 1e6 + 5;
int spf[N]; // spf[i] = smallest prime factor of i

void compute_spf()
{
    for (int i = 2; i < N; i++)
        spf[i] = i;
    for (int i = 2; i * i < N; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j < N; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

vector<pair<int, int>> factorize(int x)
{
    vector<pair<int, int>> res;
    while (x != 1)
    {
        int p = spf[x], cnt = 0;
        while (x % p == 0)
            x /= p, cnt++;
        res.emplace_back(p, cnt);
    }
    return res;
}
