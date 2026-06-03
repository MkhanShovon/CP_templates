vll kmp(string s){
    ll n=s.size();
    
    vll lps(n,0);

    fls(i,1,n-1){
        ll j=lps[i-1];
        while(j>0 && s[i]!=s[j]){
            j=lps[j-1];
        }
        if(s[i]==s[j]){
            j++;
        }
        
        lps[i]=j;
    }
    return lps;
}