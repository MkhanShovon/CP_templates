vll dp(10005, -1);
ll k;

ll mex(vll v)
{
    sort(vr(v));
    ll mx = 0;
    fl(i, v.size())
    {
        if (v[i] == mx)
        {
            mx++;
        }
    }
    return mx;
}


ll calcGrundy(ll n){
    if(n<=0){
        return 0;
    }
    else if(dp[n]!=-1){
        return dp[n];
    }
    vll v;
    fl(i,k){
        if(n-s[i]>=0){
            v.pb(calcGrundy(n-s[i]));
        }
    }
    return dp[n]=mex(v);
}

// xor => each pile grundy (when all piles are independent)
// grundy => in a pile the mex of all options