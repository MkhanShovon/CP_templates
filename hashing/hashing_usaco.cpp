#include <bits/stdc++.h>

using namespace std;

// BeginCodeSnip{Hashing Template (from the module)}
class HashedString {
  private:
	// change M and B if you want
	static const long long M = 1e9 + 9;
	static const long long B = 9973;

	// pow[i] contains B^i % M
	static vector<long long> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	vector<long long> p_hash;

  public:
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() <= s.size()) { pow.push_back((pow.back() * B) % M); }

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	long long get_hash(int start, int end) {
		long long raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
};
vector<long long> HashedString::pow = {1};
// EndCodeSnip

int main() {
	string s;
	cin >> s;

	int sz = s.size();  // just a shorthand
	int ans = 0;

	// Double the string to make it circular and avoid working with modulo
	s += s;
	HashedString pref(s);
	for (int i = 0; i < sz; i++) {
		// Binary search for the first different character
		int lo = 0;
		int hi = sz - 1;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			// Check if prefixes match
			if (pref.get_hash(i, i + mid) == pref.get_hash(ans, ans + mid)) {
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}

		// Update answer
		if (s[i + lo] < s[ans + lo]) { ans = i; }
	}

	cout << s.substr(ans, sz) << endl;
}