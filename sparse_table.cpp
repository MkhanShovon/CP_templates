#include <bits/stdc++.h>
using namespace std;

// Sparse Table Template for Range Minimum Query (RMQ)
// This can be adapted for other associative operations like max, gcd, etc.
// Time Complexity: O(N log N) preprocessing, O(1) per query

template <typename T>
class SparseTable {
private:
    vector<vector<T>> st; // Sparse table: st[i][j] = min of arr[i..i+(1<<j)-1]
    vector<int> log;      // Precomputed logarithms for quick floor(log2) calculation
    int n;                // Size of the input array
    
    // Function to combine two values (min for RMQ; change for other ops)
    T combine(const T& a, const T& b) const {
        return min(a, b); // Adapt this: e.g., max(a,b), gcd(a,b), a+b, etc.
    }

public:
    // Constructor: Builds the sparse table from the input array
    SparseTable(const vector<T>& arr) {
        n = arr.size();
        if (n == 0) return;
        
        // Precompute log values
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; ++i) {
            log[i] = log[i / 2] + 1;
        }
        
        // Initialize sparse table
        int max_log = log[n] + 1;
        st.assign(n, vector<T>(max_log));
        
        // Base case: st[i][0] = arr[i]
        for (int i = 0; i < n; ++i) {
            st[i][0] = arr[i];
        }
        
        // Fill the table using DP
        for (int j = 1; j < max_log; ++j) {
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                st[i][j] = combine(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
    
    // Query: Get the minimum in range [l, r] (0-based indices, inclusive)
    T query(int l, int r) const {
        if (l > r || l < 0 || r >= n) {
            throw out_of_range("Invalid query range");
        }
        int len = r - l + 1;
        int k = log[len];
        return combine(st[l][k], st[r - (1 << k) + 1][k]);
    }
    
    // Get the size of the array
    int size() const {
        return n;
    }
};

// Example usage
int main() {
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    SparseTable<int> st(arr);
    
    // Query examples
    cout << "Min in [0,10]: " << st.query(0, 10) << endl; // 1
    cout << "Min in [2,5]: " << st.query(2, 5) << endl;   // 1
    cout << "Min in [6,9]: " << st.query(6, 9) << endl;   // 2
    
    return 0;
}