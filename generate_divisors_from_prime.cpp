vll divs;
    function<void(ll, ll)> genDivs = [&](ll idx, ll curr)
    {
        if(idx == len(fac))
        {
            divs.pb(curr);
            return;
        }
        auto [p, c] = fac[idx];
        for(ll i = 0; i <= c; i++)
        {
            genDivs(idx + 1, curr);
            curr *= p;
        }
    };

    genDivs(0, 1);
