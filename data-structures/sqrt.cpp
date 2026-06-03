#include <bits/stdc++.h>
using namespace std;

struct SqrtRangeAddRangeQuery {
    int n, B, numBlocks;
    std::vector<long long> a;      // base values
    std::vector<long long> lazy;   // lazy add per block
    std::vector<long long> blockSum; // sum of each block (excluding lazy)

    SqrtRangeAddRangeQuery(const std::vector<long long>& arr) {
        n = (int)arr.size();
        B = (int)std::floor(std::sqrt(std::max(1, n))) + 1; // block size
        numBlocks = (n + B - 1) / B;
        a = arr;
        lazy.assign(numBlocks, 0);
        blockSum.assign(numBlocks, 0);

        // Initialize block sums
        for (int i = 0; i < n; ++i) {
            blockSum[i / B] += a[i];
        }
    }

    // Add u to [l, r] (0-indexed)
    void add(int l, int r, long long u) {
        int bl = l / B, br = r / B;
        if (bl == br) {
            for (int i = l; i <= r && i < n; ++i) {
                a[i] += u;
                blockSum[bl] += u;
            }
            return;
        }

        // Left tail
        int leftEnd = (bl + 1) * B - 1;
        for (int i = l; i <= leftEnd && i < n; ++i) {
            a[i] += u;
            blockSum[bl] += u;
        }

        // Whole blocks
        for (int b = bl + 1; b <= br - 1; ++b) {
            lazy[b] += u;
            blockSum[b] += u * (std::min(n, (b + 1) * B) - b * B);
        }

        // Right tail
        for (int i = br * B; i <= r && i < n; ++i) {
            a[i] += u;
            blockSum[br] += u;
        }
    }

    // Get value at position k (0-indexed)
    long long getPoint(int k) const {
        return a[k] + lazy[k / B];
    }

    // Get sum of range [l, r] (0-indexed)
    long long getRange(int l, int r) const {
        long long sum = 0;
        int bl = l / B, br = r / B;

        if (bl == br) {
            for (int i = l; i <= r && i < n; ++i) {
                sum += a[i] + lazy[bl];
            }
            return sum;
        }

        // Left tail
        int leftEnd = (bl + 1) * B - 1;
        for (int i = l; i <= leftEnd && i < n; ++i) {
            sum += a[i] + lazy[bl];
        }

        // Whole blocks
        for (int b = bl + 1; b <= br - 1; ++b) {
            sum += blockSum[b] + lazy[b] * (std::min(n, (b + 1) * B) - b * B);
        }

        // Right tail
        for (int i = br * B; i <= r && i < n; ++i) {
            sum += a[i] + lazy[br];
        }

        return sum;
    }
};

int main() {
    // Example usage
    std::vector<long long> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    SqrtRangeAddRangeQuery sq(arr);

    // Print initial array
    std::cout << "Initial array: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << sq.getPoint(i) << " ";
    }
    std::cout << "\n";

    // Add 10 to range [2, 5]
    sq.add(2, 5, 10);
    std::cout << "After adding 10 to range [2, 5]: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << sq.getPoint(i) << " ";
    }
    std::cout << "\n";

    // Get point query at index 3
    std::cout << "Point query at index 3: " << sq.getPoint(3) << "\n";

    // Get range sum query for [1, 4]
    std::cout << "Range sum query [1, 4]: " << sq.getRange(1, 4) << "\n";

    // Add 5 to range [0, 7]
    sq.add(0, 7, 5);
    std::cout << "After adding 5 to range [0, 7]: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << sq.getPoint(i) << " ";
    }
    std::cout << "\n";

    // Get range sum query for [0, 7]
    std::cout << "Range sum query [0, 7]: " << sq.getRange(0, 7) << "\n";

    return 0;
}

// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> a[i];
//     }
//     int len = (int)sqrt(n + .0) + 1; // size of the block and the number of blocks
//     vector<int> b(len);
//     for (int i = 0; i < n; ++i)
//         b[i / len] += a[i];

//     int q;
//     cin >> q;
//     // answering the queries
//     while (q--)
//     {
//         int l, r;
//         cin >> l >> r;
//         // read input data for the next query
//         int sum = 0;
//         for (int i = l; i <= r;)
//         {
//             if (i % len == 0 && i + len - 1 <= r)
//             {
//                 // if the whole block starting at i belongs to [l, r]
//                 sum += b[i / len];
//                 i += len;
//             }
//             else
//             {
//                 sum += a[i];
//                 ++i;
//             }
//         }
//     }
// }