template<typename T>
struct OrderedMultiset {
  int id;
  ordered_set<pair<T,int>> st;
  OrderedMultiset() { id = 0; }
  void insert(T val) { st.insert({val, id++}); }
  void erase(T val) { st.erase(st.lower_bound({val, 0})); }
  int order_of_key(T val) { return st.order_of_key({val, 0}); }
  T find_by_order(int val) { pair<T,int> p = *st.find_by_order(val); return p.first; }
  typename ordered_set<pair<T,int>>::iterator lower_bound(T val) { return st.lower_bound({val, 0}); }
  typename ordered_set<pair<T,int>>::iterator upper_bound(T val) { return st.upper_bound({val, id}); }
  int size() { return st.size(); }
  void clear() { st = ordered_set<pair<T,int>>(); }
  /*
    has(T val)
    count(T val)
  */
};
