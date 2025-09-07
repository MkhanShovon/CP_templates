#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
using namespace std;
using std::cout;
using std::cin;
using std::endl;
using ll=long long;
using ld=long double;
const ll ILL=2167167167167167167;
const int INF=2100000000;
const int mod=998244353;
#define rep(i,a,b) for (int i=(int)(a);i<(int)(b);i++)
#define all(p) p.begin(),p.end()
template<class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
template<class T> ll LB(vector<T> &v,T a){return lower_bound(v.begin(),v.end(),a)-v.begin();}
template<class T> ll UB(vector<T> &v,T a){return upper_bound(v.begin(),v.end(),a)-v.begin();}
template<class T> bool chmin(T &a,T b){if(a>b){a=b;return 1;}else return 0;}
template<class T> bool chmax(T &a,T b){if(a<b){a=b;return 1;}else return 0;}
template<class T> void So(vector<T> &v) {sort(v.begin(),v.end());}
template<class T> void Sore(vector<T> &v) {sort(v.begin(),v.end(),[](T x,T y){return x>y;});}
void yneos(bool a,bool upp=0){if(a) cout<<(upp?"YES\n":"Yes\n"); else cout<<(upp?"NO\n":"No\n");}
template<class T> void vec_out(vector<T> &p,int ty=0){
if(ty==2){cout<<'{';for(int i=0;i<(int)p.size();i++){if(i){cout<<",";}cout<<'"'<<p[i]<<'"';}cout<<"}\n";}
else{if(ty==1){cout<<p.size()<<"\n";}for(int i=0;i<(int)(p.size());i++){if(i) cout<<" ";cout<<p[i];}cout<<"\n";}}
template<class T> T vec_min(vector<T> &a){assert(!a.empty());T ans=a[0];for(auto &x:a) chmin(ans,x);return ans;}
template<class T> T vec_max(vector<T> &a){assert(!a.empty());T ans=a[0];for(auto &x:a) chmax(ans,x);return ans;}
template<class T> T vec_sum(vector<T> &a){T ans=T(0);for(auto &x:a) ans+=x;return ans;}
int pop_count(long long a){int res=0;while(a){res+=(a&1),a>>=1;}return res;}
//a*x+b*y=gcd(a,b)となるx,yにする　返り値gcd(a,b)
ll Euclid(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    ll d=Euclid(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

// val1=(a,p) val2=(b,q)
// return (c,r)
// c: c%p==a && c%q==b
// r: r=lcm(a,b)
// need: a%gcd(p,q)==b%gcd(p,q)
// use: Euclid
std::pair<long long,long long> ctr_sub(std::pair<long long,long long> val1,std::pair<long long,long long> val2){
	long long a,b,p,q;
	long long X,Y,G,ans_val,ans_mod;
	tie(a,p)=val1;
	tie(b,q)=val2;
	G=Euclid(p,q,X,Y);
	if((b-a)%G!=0) return {-1,-1};
	ans_mod=p*(q/G);
	ans_val=(p*((X*((b-a)/G))%q))%ans_mod+a;
	return {(ans_val%ans_mod+ans_mod)%ans_mod,ans_mod};
}


void solve();
// oddloop
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t=1;
    //cin>>t;
    rep(i,0,t) solve();
}

void solve(){
    ll X,Y;
    cin>>X>>Y;
    ll a,b;
    auto g=Euclid(abs(X),abs(Y),a,b);
    if(g>2){
        cout<<"-1\n";
    }
    else{
        if(g==1) a*=2,b*=2;
        b*=-1;
        if(X<0) a*=-1;
        if(Y<0) b*=-1;
        cout<<b<<" "<<a<<endl;
    }
}