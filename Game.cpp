vll dp(10005, -1);
ll k;

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
    return dp[n]=mex2(v);
}