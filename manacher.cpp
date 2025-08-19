vll manacher(const string& s) {
    ll n = s.size();
    string t = "#";
    for (char c : s) t += c + string("#");
    ll m = t.size();
    vll p(m, 0);
    ll c = 0, r = 0;
    fl(i, m) {
        ll mirror = 2 * c - i;
        if (i < r) p[i] = min(r - i, p[mirror]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m && t[i - p[i] - 1] == t[i + p[i] + 1]) p[i]++;
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
    return p;
}
