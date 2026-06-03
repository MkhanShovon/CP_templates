    vpll v(q);
    cin >> v;
    
    vll mxr(n + 1);
    for(auto [l, r] : v){
        mxr[l] = max(mxr[l], r);
    }

    ll mr = 0;
    vpll rng;
    fls(i, 1, n){
        if(mxr[i] > mr){
            rng.pb({i, mxr[i]});
            mr = mxr[i];
        }
    }
