#include <iostream>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 2e6 + 20;

ll fac[MAXN + 1];
ll inv[MAXN + 1];

// BeginCodeSnip{Counting functions}
ll exp(ll x, ll n, ll m)
{
	x %= m;
	ll res = 1;
	while (n > 0)
	{
		if (n % 2 == 1)
		{
			res = res * x % m;
		}
		x = x * x % m;
		n /= 2;
	}
	return res;
}

// Calculate modular inverse of a number using Fermat's Little Theorem
// Works when MOD is prime
ll inverse(ll a)
{
	return exp(a, MOD - 2, MOD);
}

// Calculate modular inverse using Extended Euclidean Algorithm
// Works for any modulus (not necessarily prime)
ll extgcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll gcd = extgcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return gcd;
}

ll inverse_general(ll a, ll m)
{
	ll x, y;
	ll gcd = extgcd(a, m, x, y);
	if (gcd != 1)
	{
		return -1; // Inverse doesn't exist
	}
	return (x % m + m) % m;
}

void factorial()
{
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++)
	{
		fac[i] = fac[i - 1] * i % MOD;
	}
}

void inverses()
{
	inv[MAXN] = exp(fac[MAXN], MOD - 2, MOD);
	for (int i = MAXN; i >= 1; i--)
	{
		inv[i - 1] = inv[i] * i % MOD;
	}
}

ll choose(int n, int r)
{
	if(n < 0 or r < 0 or n < r) return 0;
	return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}
ll add(ll a, ll b) { return (a + b) % MOD; }
ll sub(ll a, ll b) { return (a - b + MOD) % MOD; }
ll mul(ll a, ll b) { return (a * b) % MOD; }
// factorial();
// inverses();


ll dp[35][35];
ll ncr(int n, int r)
{
	if (n == r || r == 0)
		return 1;
	else if (r == 1)
		return n;
	else if (dp[n][r] != (-1))
		return dp[n][r];
	dp[n][r] = ncr(n - 1, r) + ncr(n - 1, r - 1);
	return dp[n][r];
}

// without MOD
long long comb(int n, int k)
{
	if(n < 0 or k < 0 or n < k){
        return 0;
    }
	if (k > n - k)
	{
		k = n - k;
	}
	long long ret = 1;
	for (int i = 0; i < k; i++)
	{
		// this is done instead of *= for divisibility issues
		ret = (ret * (n - i)) / (i + 1);
	}
	return ret;
}

bool isBinomialOdd(long long n, long long r)
{
	// Check if n AND r == r
	return (n & r) == r;
}
// EndCodeSnip

int main()
{
	factorial();
	inverses();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		cout << choose(a, b) << '\n';
	}
}

//stars and bars = choose(n + k - 1, k - 1) 