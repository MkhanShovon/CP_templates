#include<bits/stdc++.h>
using namespace std;    
using ll = long long;
using vpll = vector<pair<ll, ll>> ;

// Function to find all prime factors of a number
vpll prime_factorization(int n)
{ // O(sqrt(n))
    vpll factors;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ll cnt = 0;
            while (n % i == 0)
            {
                cnt++;
                n /= i;
            }
            factors.push_back({i, cnt});
        }
    }
    if (n > 1)
    {
        factors.push_back({n, 1});
    }
    return factors;
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