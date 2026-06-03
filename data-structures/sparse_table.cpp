#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SparseTable {
private:
    int n, K;
    vector<int> lg2;            // floor(log2) table
    vector<vector<T>> st;       // st[k][i] covers [i, i + 2^k - 1]
    function<T(const T&, const T&)> combine;
    T identity;
    bool idempotent;            // if true -> O(1) queries, else O(log N)

    void build(const vector<T>& a) {
        n = (int)a.size();
        if (n == 0) return;

        // precompute logs
        lg2.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg2[i] = lg2[i / 2] + 1;

        K = lg2[n] + 1;
        st.assign(K, vector<T>(n));
        // base layer
        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        // build
        for (int k = 1; k < K; ++k) {
            int len = 1 << k;
            for (int i = 0; i + len <= n; ++i) {
                st[k][i] = combine(st[k-1][i], st[k-1][i + (len >> 1)]);
            }
        }
    }

public:
    // Constructor: (identity, combine, array, idempotent?)
    SparseTable(const T& identity_,
                function<T(const T&, const T&)> combine_,
                const vector<T>& a,
                bool idempotent_ = true)
        : combine(move(combine_)), identity(identity_), idempotent(idempotent_) {
        build(a);
    }

    // Optional ctor mirroring your SegmentTree example signature
    SparseTable(size_t /*n_unused*/,
                const T& identity_,
                function<T(const T&, const T&)> combine_,
                const vector<T>& a,
                bool idempotent_ = true)
        : combine(move(combine_)), identity(identity_), idempotent(idempotent_) {
        build(a);
    }

    // Query on inclusive range [l, r]
    T query(int l, int r) const {
        if (l > r || l < 0 || r >= n) throw out_of_range("Invalid query range");
        if (idempotent) {
            int len = r - l + 1;
            int k = lg2[len];
            // two overlapping blocks of length 2^k
            return combine(st[k][l], st[k][r - (1 << k) + 1]);
        } else {
            // disjoint power-of-two decomposition (left to right)
            T res = identity;
            int pos = l;
            int len = r - l + 1;
            for (int k = 0; len > 0; ++k) {
                if (len & 1) {
                    res = combine(res, st[k][pos]);
                    pos += (1 << k);
                }
                len >>= 1;
            }
            return res;
        }
    }

    int size() const { return n; }
};

int main() {
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2};

    // Min (idempotent, O(1) query)
    SparseTable<int> stMin(
        INT_MAX,
        [](int a, int b){ return min(a, b); },
        arr,
        /*idempotent=*/true
    );
    cout << "min[1,5] = " << stMin.query(1,5) << "\n";

    // Max (idempotent, O(1) query)
    SparseTable<int> stMax(
        INT_MIN,
        [](int a, int b){ return max(a, b); },
        arr,
        true
    );
    cout << "max[1,5] = " << stMax.query(1,5) << "\n";

    // GCD (idempotent, O(1) query)
    SparseTable<int> stGcd(
        0,
        [](int a, int b){ return std::gcd(a, b); },
        arr,
        true
    );
    cout << "gcd[0,6] = " << stGcd.query(0,6) << "\n";

    // Sum (NOT idempotent, O(log N) query)
    SparseTable<long long> stSum(
        0LL,
        [](long long a, long long b){ return a + b; },
        vector<long long>(arr.begin(), arr.end()),
        /*idempotent=*/false
    );
    cout << "sum[2,6] = " << stSum.query(2,6) << "\n";

    return 0;
}
