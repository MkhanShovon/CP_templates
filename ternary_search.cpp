// Ternary search on integers to find maximum
int ternarySearch(int l, int r) {
    while (r - l > 2) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
        //for minimum use >= instead of <
            l = m1;
        else
            r = m2;
    }
    // Brute force through the remaining 2 or 3 elements
    int maxVal = f(l);
    for (int i = l + 1; i <= r; i++) {
        maxVal = max(maxVal, f(i));
    }
    return maxVal;
}

// Ternary search on doubles to find maximum
double ternarySearch(double l, double r) {
    const double eps = 1e-9;  // Precision threshold
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2))
        //for minimum use >= instead of <
            l = m1;
        else
            r = m2;
    }
    return (l + r) / 2;  // Midpoint will give the maximum value
}