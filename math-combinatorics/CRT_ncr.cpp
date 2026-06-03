#include <bits/stdc++.h>
using namespace std;

using T = __int128;
using ll = long long;

T extended_euclid(T a, T b, T &x, T &y) {
  T xx = y = 0;
  T yy = x = 1;
  while (b) {
    T q = a / b;
    T t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}

pair<T, T> CRT(T a1, T m1, T a2, T m2) {
  T p, q;
  T g = extended_euclid(m1, m2, p, q);        
  if ((a1 % g + g) % g != (a2 % g + g) % g) return {0, -1};
  T m = m1 / g * m2;                          
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  T res = (p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) % m;
  if (res < 0) res += m;
  return {res, m};
}

long long modpow(long long a, long long e, long long mod) {
  long long r = 1 % mod;
  a %= mod; if (a < 0) a += mod;
  while (e) {
    if (e & 1) r = (long long)((__int128)r * a % mod);
    a = (long long)((__int128)a * a % mod);
    e >>= 1;
  }
  return r;
}

struct Tables {
  vector<int> fact, invfact;
};
unordered_map<int, Tables> tbl;

const Tables& get_tables(int p) {
  auto it = tbl.find(p);
  if (it != tbl.end()) return it->second;
  Tables T;
  T.fact.assign(p, 1);
  T.invfact.assign(p, 1);
  for (int i = 1; i < p; ++i) T.fact[i] = (int)(1LL * T.fact[i-1] * i % p);
  T.invfact[p-1] = (int)modpow(T.fact[p-1], p-2, p);
  for (int i = p-2; i >= 0; --i) T.invfact[i] = (int)(1LL * T.invfact[i+1] * (i+1) % p);
  auto [it2, _] = tbl.emplace(p, move(T));
  return it2->second;
}

int nCk_small_mod_p(int n, int k, int p) {
  if (k < 0 || k > n) return 0;
  const auto& T = get_tables(p);
  int res = T.fact[n];
  res = (int)(1LL * res * T.invfact[k] % p);
  res = (int)(1LL * res * T.invfact[n - k] % p);
  return res;
}

int nCk_mod_prime_lucas(long long n, long long k, int p) {
  if (k < 0 || k > n) return 0;
  int ans = 1;
  while (n > 0 || k > 0) {
    int ni = (int)(n % p);
    int ki = (int)(k % p);
    if (ki > ni) return 0;
    ans = (int)(1LL * ans * nCk_small_mod_p(ni, ki, p) % p);
    n /= p; k /= p;
  }
  return ans;
}

vector<int> small_primes() { return {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47}; }

vector<int> factor_squarefree_M(long long M) {
  vector<int> ps;
  for (int p : small_primes()) {
    if (M % p == 0) {
      ps.push_back(p);
      M /= p;
      while (M % p == 0) M /= p;
    }
  }
  return ps;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int TC; 
  if (!(cin >> TC)) return 0;
  while (TC--) {
    long long N, R, M;
    cin >> N >> R >> M;

    if (M == 1) { cout << 0 << '\n'; continue; }
    if (R < 0 || R > N) { cout << 0 << '\n'; continue; }

    vector<int> primes = factor_squarefree_M(M);

    pair<T,T> cur = {0, 1}; 
    for (int p : primes) {
      int r = nCk_mod_prime_lucas(N, R, p);
      auto nxt = CRT(cur.first, cur.second, (T)r, (T)p);
      if (nxt.second == -1) { 
        cout << 0 << '\n';
        goto next_case;
      }
      cur = nxt;
    }

    cout << (long long)(cur.first % M) << '\n';
  next_case:
    (void)0;
  }
  return 0;
}
