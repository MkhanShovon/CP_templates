# SOS DP and Prefix Sum Insights

## 1. Problem Statement
We are given an array `A` of size `2^N`. Each index `mask` corresponds to a subset of `{0,1,...,N-1}`. We want to compute:

```
F[mask] = sum(A[i] for i subset of mask)
```

This is also known as the **zeta transform over subsets**.

---

## 2. Naive and Better Solutions
### Brute Force
```cpp
for (int mask = 0; mask < (1<<N); mask++) {
    for (int i = 0; i < (1<<N); i++) {
        if ((mask & i) == i)  // i is subset of mask
            F[mask] += A[i];
    }
}
```
- Complexity: `O(4^N)`.

### Subset Iteration
```cpp
for (int mask = 0; mask < (1<<N); mask++) {
    for (int sub = mask; sub > 0; sub = (sub-1) & mask)
        F[mask] += A[sub];
    F[mask] += A[0]; // empty subset
}
```
- Complexity: `O(3^N)`.

---

## 3. Optimized SOS DP
Efficient version using **bit DP**:
```cpp
for (int mask = 0; mask < (1<<N); mask++)
    F[mask] = A[mask];

for (int bit = 0; bit < N; bit++) {
    for (int mask = 0; mask < (1<<N); mask++) {
        if (mask & (1<<bit))
            F[mask] += F[mask ^ (1<<bit)];
    }
}
```
- Complexity: `O(N * 2^N)`.

---

## 4. Prefix Sum Analogy
SOS DP is really just a **multi-dimensional prefix sum**.

Example for N=2:
```
M[0][0] = A[00], M[0][1] = A[01]
M[1][0] = A[10], M[1][1] = A[11]
```

2D prefix sums:
```cpp
// row-wise
for (int i = 1; i < 2; i++)
    for (int j = 0; j < 2; j++)
        M[i][j] += M[i-1][j];

// column-wise
for (int i = 0; i < 2; i++)
    for (int j = 1; j < 2; j++)
        M[i][j] += M[i][j-1];
```

After this, `M[i][j]` = sum of all `A[x][y]` with `x <= i, y <= j`, which is exactly the subset relation.

---

## 5. Variants
### Sum Over Supersets
Instead of subsets:
```cpp
for (int i = 0; i < (1<<N); i++) F[i] = A[i];

for (int bit = 0; bit < N; bit++) {
    for (int mask = 0; mask < (1<<N); mask++) {
        if ((mask & (1<<bit)) == 0) // different condition
            F[mask] += F[mask ^ (1<<bit)];
    }
}
```

### Inverse Transform (Möbius)
Recover A from F:
```cpp
for (int i = 0; i < (1<<N); i++) A[i] = F[i];

for (int bit = 0; bit < N; bit++) {
    for (int mask = 0; mask < (1<<N); mask++) {
        if (mask & (1<<bit))
            F[mask] -= F[mask ^ (1<<bit)];
    }
}
```

---

## 6. General Multi-Dimensional Prefix Sums
For arbitrary dimensions `[d1, d2, d3, ...]`, flatten indices with block sizes:

```cpp
int N = 4;
vector<int> dims = {6, 9, 4, 20};
vector<int> blocks(N+1);

blocks[0] = 1;
for (int i = 0; i < N; i++)
    blocks[i+1] = blocks[i] * dims[i];

for (int idx = 0; idx < blocks[N]; idx++)
    F[idx] = A[idx];

for (int d = 0; d < N; d++) {
    for (int idx = 0; idx < blocks[N]; idx++) {
        if ((idx / blocks[d]) % dims[d] != 0)
            F[idx] += F[idx - blocks[d]];
    }
}
```

This is the generalization of SOS DP.

---

## 7. Key Takeaways
- SOS DP is **prefix sums over N binary dimensions**.
- Complexity improvement: `O(4^N)` → `O(3^N)` → `O(N*2^N)`.
- Thinking in terms of prefix sums:
  - Explains the implementation naturally.
  - Makes supersets and inversion variants obvious.
  - Extends to general multidimensional prefix sums.
