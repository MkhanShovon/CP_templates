#include <bits/stdc++.h>
using namespace std;

// d1: odd pal radii, d2: even pal radii
// Time: O(n), Space: O(n)
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = (int)s.size();
    vector<int> d1(n), d2(n);

    // ---- odd ----
    // current rightmost palindrome is [l, r] (inclusive)
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = 1;
        if (i <= r) k = min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k;
        if (i + k - 1 > r) { l = i - (k - 1); r = i + (k - 1); }
    }

    // ---- even ----
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = 0;
        if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k;
        if (i + k - 1 > r) { l = i - k; r = i + k - 1; }
    }

    return {d1, d2};
}

string longest_palindrome(const string &s) {
    auto [d1, d2] = manacher(s);
    int n = (int)s.size();

    int bestLen = 0, bestL = 0;

    // odd
    for (int i = 0; i < n; i++) {
        int len = 2 * d1[i] - 1;
        if (len > bestLen) {
            bestLen = len;
            bestL = i - (d1[i] - 1);
        }
    }
    // even
    for (int i = 0; i < n; i++) {
        int len = 2 * d2[i];
        if (len > bestLen) {
            bestLen = len;
            bestL = i - d2[i];
        }
    }
    return s.substr(bestL, bestLen);
}

long long count_palindromes(const string &s) {
    auto [d1, d2] = manacher(s);
    long long cnt = 0;
    for (int v : d1) cnt += v;     // odd centers
    for (int v : d2) cnt += v;     // even centers
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; 
    if (!(cin >> s)) return 0;

    auto [d1, d2] = manacher(s);
    cout << "Longest: " << longest_palindrome(s) << "\n";
    cout << "Total pal substrings: " << count_palindromes(s) << "\n";

    // Example: print max odd/even around each center (as lengths)
    // Odd length at i:
    //   len_odd[i] = 2*d1[i]-1
    // Even length centered between i-1 and i:
    //   len_even[i] = 2*d2[i]
    return 0;
}
