
/*
======================  Catalan Numbers: handy formulas  ======================

Definitions / Recurrences
-------------------------
(1) Catalan convolution (classic DP):
C_0 = 1
C_{n+1} = sum_{i=0}^{n} C_i * C_{n-i}
C_n = (2 * (2 * n - 1) / (n + 1)) * C_n-1

(2) Linear (ratio) recurrence:
(n+2) * C_{n+1} = 2 * (2n+1) * C_n
⇔ C_n = C_{n-1} * [ 2 * (2n - 1) / (n + 1) ],  for n >= 1

Closed forms
------------
(3) Binomial / factorial forms:
C_n = (1/(n+1)) * binom(2n, n)
= binom(2n, n) - binom(2n, n+1)
= (2n)! / ( n! * (n+1)! )

(4) Product form:
C_n = ∏_{k=2}^{n} (n + k) / k
(equivalently C_n = binom(2n, n) / (n+1))

Generating function
-------------------
(5) C(x) = sum_{n>=0} C_n x^n = (1 - sqrt(1 - 4x)) / (2x)

Asymptotics
-----------
(6) C_n ~ 4^n / ( n^{3/2} * sqrt(pi) )

First values
------------
(7) 1, 1, 2, 5, 14, 42, 132, 429, 1430, ...

Mod notes (for coding)
----------------------
• DP O(n^2) via (1) works well for moderate n (like this function).
• Faster O(n) per term via (2) needs modular inverses of (n+1) under prime MOD.
• For (3)/(4) under MOD, use factorials + inv factorials, or multiply with modular inverses.
===============================================================================
*/
const int MOD = 1e9+7;
const int MAX = 1000;
int catalan[MAX+1];

void init(int n) {
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] = (catalan[i] + 1LL * catalan[j] * catalan[i-j-1]) % MOD;
        }
    }
}
