    ll subtract = 0;
    auto generate = [&](auto&& self, ll cur, int idx) -> void {
        if (idx == (int)fac.size())
        {
            if (cur < m) subtract++;
            return;
        }
        ll p = fac[idx].ff;
        ll e = fac[idx].ss;
        ll mul = 1;
        for (int j = 0; j <= e; j++)
        {
            self(self, cur * mul, idx + 1);
            mul *= p;
        }
    };
    generate(generate, 1LL, 0);
