template <class T>
struct BIT { //1-indexed
  int n; vector<T> t;
  BIT() {}
  void init(int _n) {
    n = _n; t.assign(n + 1, 0);
  }
  T query(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
  void upd(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
  }
  void upd(int l, int r, T val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
    ll bit_search(ll v){//lower bound
        ll sum=0;
        ll pos=0;
        ll N=bit.size();
        for(ll i=log2(N)+1;i>=0;i--){
            if(pos+(1<<i)<N && sum+bit[pos+(1<<i)]<v){
                sum+=bit[pos+(1<<i)];
                pos+=(1<<i);
            }
        }
        return pos+1;
    }
};