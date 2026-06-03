template <typename T>
struct BIT {
private:
    size_t n; // Size of the BIT (1-indexed)
    std::vector<T> t; // Internal array for BIT
    T neutral_value; // Neutral value for the operation (e.g., 0 for sum)

public:
    // Constructor: Initializes BIT with given size and neutral value
    BIT(size_t size = 0, T neutral = T()) {
        if (size > 0) init(size, neutral);
    }

    // Initialize the BIT with size and neutral value
    // T must support addition, subtraction, and comparison for bit_search
    void init(size_t size, T neutral = T()) {
        if (size == 0) throw std::invalid_argument("Size must be positive");
        n = size;
        neutral_value = neutral;
        t.assign(n + 1, neutral_value);
    }

    // Query prefix sum up to index i (1-based)
    T query(size_t i) const {
        if (i > n) throw std::invalid_argument("Query index out of bounds");
        T ans = neutral_value;
        for (; i >= 1; i -= (i & -i)) {
            ans = ans + t[i];
        }
        return ans;
    }

    // Update index i (1-based) by adding val
    void upd(size_t i, T val) {
        if (i < 1 || i > n) throw std::invalid_argument("Update index out of bounds");
        for (; i <= n; i += (i & -i)) {
            t[i] = t[i] + val;
        }
    }

    // Update range [l, r] (1-based) by adding val
    void upd(size_t l, size_t r, T val) {
        if (l < 1 || r > n || l > r) throw std::invalid_argument("Invalid range update bounds");
        upd(l, val);
        if (r < n) upd(r + 1, -val);
    }

    // Query sum over range [l, r] (1-based)
    T query(size_t l, size_t r) const {
        if (l < 1 || r > n || l > r) throw std::invalid_argument("Invalid range query bounds");
        return query(r) - query(l - 1);
    }

    // Find the smallest index i (1-based) such that query(i) >= v
    // Returns n + 1 if no such index exists
    size_t bit_search(T v) const {
        if (v <= neutral_value) return 1; // Handle cases where v is too small
        T sum = neutral_value;
        size_t pos = 0;
        size_t log_n = static_cast<size_t>(std::log2(n) + 1);
        for (size_t i = log_n; i != size_t(-1); --i) {
            size_t next_pos = pos + (1ULL << i);
            if (next_pos <= n && sum + t[next_pos] < v) {
                sum = sum + t[next_pos];
                pos = next_pos;
            }
        }
        return pos + 1;
    }

    void clear() {
        t.assign(n + 1, neutral_value);
    }
};