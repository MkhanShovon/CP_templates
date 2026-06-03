#include <bits/stdc++.h>
using namespace std;
#define bint __int128
#define int long long
#define ll long long
#define pb push_back
#define F first
#define S second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (n); i++)
#define fore(i, a, b) for (int i = (a); i < (b); i++)
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0);
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef map<int,int> mp;
typedef priority_queue<int> pq;
const int MOD = 1e7;
const ll INF = 4e18;

struct Hash {
    bint MOD=212345678987654321LL, P=1777771, PI=1069557410896959571LL;
    vector<bint> h,pi;
    Hash(string& s){
        assert((P*PI)%MOD==1);
        h.resize(s.size()+1); pi.resize(s.size()+1);
        h[0]=0; pi[0]=1;
        bint p=1;
        for (int i=1; i<=s.size(); ++i) {
            h[i]=(h[i-1]+p*s[i-1])%MOD;
            pi[i]=(pi[i-1]*PI)%MOD;
            p=(p*P)%MOD;
        }
    }
    long long get(int s, int e){
        return (((h[e]-h[s]+MOD)%MOD)*pi[s])%MOD;
    }
};

signed main(){
    string cad;cin >> cad;
    Hash h(cad);
    int q; cin >> q;
    while(q--){
        int l, r; cin >> l >> r;
        cout << h.get(l, r) << endl;
    }
    return 0;
}
