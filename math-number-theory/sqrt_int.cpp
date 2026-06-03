ll sqrt_int(ll x) {
    if (x == 0 || x == 1) return x;
    ll l = 1, r = min(x, 2000000000LL);
    while (l < r) {
        ll m = l + (r - l + 1) / 2;
        if (m <= x / m) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}
