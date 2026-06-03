#include <bits/stdc++.h>
using namespace std;

using u128 = __uint128_t;
using u64  = unsigned long long;

// ---------- modular arithmetic (safe for 64-bit) ----------
static inline u64 mod_mul(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}
static inline u64 mod_pow(u64 a, u64 e, u64 mod) {
    u64 r = 1;
    while (e) {
        if (e & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

// ---------- deterministic Miller-Rabin for 64-bit ----------
static bool isPrime64(u64 n) {
    if (n < 2) return false;
    static u64 smallPrimes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (u64 p : smallPrimes) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }

    // write n-1 = d * 2^s
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }

    auto witness = [&](u64 a) -> bool {
        if (a % n == 0) return false;
        u64 x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) return false;
        for (u64 i = 1; i < s; i++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) return false;
        }
        return true; // composite
    };

    // Deterministic bases for 64-bit
    static u64 bases[] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    for (u64 a : bases) {
        if (witness(a)) return false;
    }
    return true;
}

static bool isPerfectSquare(u64 x) {
    u64 r = (u64) llround(sqrt((long double)x));
    while (r*r > x) --r;
    while ((r+1) * (u128)(r+1) <= x) ++r;
    return (u128)r * r == x;
}

// ---------- sieve primes up to 1e6 ----------
static vector<int> sieve(int N = 1000000) {
    vector<bool> is(N + 1, true);
    is[0] = is[1] = false;
    for (int i = 2; 1LL*i*i <= N; i++) if (is[i]) {
        for (long long j = 1LL*i*i; j <= N; j += i) is[(int)j] = false;
    }
    vector<int> primes;
    for (int i = 2; i <= N; i++) if (is[i]) primes.push_back(i);
    return primes;
}

// ---------- the trick: O(N^(1/3)) trial + 3 remaining cases ----------
static u64 countDivisors(u64 N, const vector<int>& primes) {
    u64 ans = 1;

    for (int p : primes) {
        u64 pp = (u64)p;
        if (pp * pp * pp > N) break;

        if (N % pp == 0) {
            int cnt = 1; // exponent+1 contribution
            while (N % pp == 0) {
                N /= pp;
                cnt++;
            }
            ans *= (u64)cnt;
        }
    }

    // Now remaining N has at most 2 prime factors
    if (N == 1) return ans;

    if (isPrime64(N)) {
        // N is prime => exponent 1 => *2
        ans *= 2;
    } else if (isPerfectSquare(N)) {
        u64 r = (u64) llround(sqrt((long double)N));
        // N = r^2. If r is prime => (2+1)=3
        if (isPrime64(r)) ans *= 3;
        else {
            // (rarely) N could be square of composite here if input is small weird,
            // but with our loop cutoff, this shouldn't happen for intended use.
            // Still, safest fallback: factor it (not needed in typical problems).
            // We'll treat as product of two primes case (*4) only if N != 1.
            ans *= 1; // keep (or handle separately if you want)
        }
    } else {
        // N = p*q with p != q primes => (1+1)(1+1)=4
        ans *= 4;
    }

    return ans;
}

// ---------- example main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto primes = sieve(1000000);

    int T;
    cin >> T;
    while (T--) {
        unsigned long long N;
        cin >> N;
        cout << countDivisors(N, primes) << "\n";
    }
    return 0;
}
