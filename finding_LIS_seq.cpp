#include <bits/stdc++.h>
using namespace std;

// Enhanced Segment Tree that can track both max value and its index
class AdvancedSegTree {
private:
    int len;
    vector<pair<int, int>> segtree; // Stores (value, index) pairs
    
public:
    AdvancedSegTree(int len) : len(len), segtree(2 * len, {INT32_MIN, -1}) {}
    
    void set(int ind, int val, int idx) {
        ind += len;
        segtree[ind] = {val, idx};
        for (; ind > 1; ind >>= 1) {
            segtree[ind >> 1] = max(segtree[ind], segtree[ind ^ 1]);
        }
    }
    
    pair<int, int> range_max(int from, int to) {
        pair<int, int> res = {INT32_MIN, -1};
        for (from += len, to += len; from < to; from >>= 1, to >>= 1) {
            if (from & 1) res = max(res, segtree[from++]);
            if (to & 1) res = max(res, segtree[--to]);
        }
        return res;
    }
};

// Finds LIS and can reconstruct the sequence
vector<int> find_lis_sequence(const vector<int>& a) {
    if (a.empty()) return {};
    
    // Coordinate compression
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    map<int, int> coord_comp;
    int cidx = 0;
    for (int i = 0; i < sorted.size(); i++) {
        if (i == 0 || sorted[i] != sorted[i-1]) {
            coord_comp[sorted[i]] = cidx++;
        }
    }
    
    AdvancedSegTree st(cidx);
    vector<int> prev(a.size(), -1); // For reconstruction
    
    for (int i = 0; i < a.size(); i++) {
        int comp = coord_comp[a[i]];
        auto [max_val, max_idx] = st.range_max(0, comp);
        
        int current_len = (max_val != INT32_MIN) ? max_val + 1 : 1;
        prev[i] = (max_val != INT32_MIN) ? max_idx : -1;
        st.set(comp, current_len, i);
    }
    
    // Reconstruct the sequence
    auto [lis_len, last_idx] = st.range_max(0, cidx);
    vector<int> lis;
    for (int i = last_idx; i != -1; i = prev[i]) {
        lis.push_back(a[i]);
    }
    reverse(lis.begin(), lis.end());
    return lis;
}

// Weighted LIS version (max sum instead of max length)
int weighted_lis(const vector<int>& a, const vector<int>& weights) {
    // Coordinate compression
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    map<int, int> coord_comp;
    int cidx = 0;
    for (int i = 0; i < sorted.size(); i++) {
        if (i == 0 || sorted[i] != sorted[i-1]) {
            coord_comp[sorted[i]] = cidx++;
        }
    }
    
    AdvancedSegTree st(cidx);
    
    for (int i = 0; i < a.size(); i++) {
        int comp = coord_comp[a[i]];
        auto [max_sum, _] = st.range_max(0, comp);
        int current = (max_sum != INT32_MIN) ? max_sum + weights[i] : weights[i];
        st.set(comp, current, i);
    }
    
    auto [total, _] = st.range_max(0, cidx);
    return total;
}

int main() {
    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    
    // Get LIS sequence
    auto lis = find_lis_sequence(arr);
    cout << "LIS sequence: ";
    for (int num : lis) cout << num << " ";
    cout << "\nLength: " << lis.size() << endl;
    
    // Weighted LIS example
    vector<int> weights = {1, 1, 1, 1, 1, 1, 1, 1, 1}; // Same as normal LIS
    cout << "Weighted LIS sum: " << weighted_lis(arr, weights) << endl;
    
    return 0;
}