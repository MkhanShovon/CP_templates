#include <bits/stdc++.h>
using namespace std;

/*** ===================== UNDIRECTED EULER ===================== ***/
// 0-indexed, allows multi-edges & self-loops
struct EulerUndirected {
    int n, m;
    vector<vector<pair<int,int>>> g; // (to, edge_id)
    vector<int> deg;

    // scratch
    vector<char> used;
    vector<int> it;

    EulerUndirected(int n=0): n(n), m(0), g(n), deg(n,0) {}
    void reset(int N) { *this = EulerUndirected(N); }

    int add_edge(int u, int v) {
        int id = m++;
        g[u].push_back({v, id});
        g[v].push_back({u, id});
        deg[u]++; deg[v]++;
        return id;
    }

    // connectivity among non-isolated vertices
    bool connected_ignoring_isolated(int start) {
        if (m == 0) return true; // no edges => vacuously OK for path/cycle checks
        vector<char> vis(n, 0);
        stack<int> st;
        // move to any vertex with deg>0
        int s = start;
        if (s < 0 || deg[s] == 0) {
            s = -1;
            for (int i=0;i<n;i++) if (deg[i] > 0) { s = i; break; }
            if (s == -1) return true;
        }
        st.push(s); vis[s] = 1;
        int seen = 0, need = 0;
        for (int i=0;i<n;i++) if (deg[i] > 0) need++;
        while(!st.empty()){
            int u = st.top(); st.pop();
            if (deg[u] > 0) seen++;
            for (auto [v, id] : g[u]) if (!vis[v]) vis[v]=1, st.push(v);
        }
        return seen == need;
    }

    // Hierholzer from chosen start
    vector<int> hierholzer(int start) {
        if (m == 0) return {start < 0 ? 0 : start}; // no edges
        used.assign(m, 0);
        it.assign(n, 0);
        vector<int> st, res;
        int s = start;
        if (s < 0 || deg[s] == 0) {
            for (int i=0;i<n;i++) if (deg[i] > 0){ s=i; break; }
        }
        st.push_back(s);
        while(!st.empty()){
            int v = st.back();
            while (it[v] < (int)g[v].size() && used[g[v][it[v]].second]) it[v]++;
            if (it[v] == (int)g[v].size()){
                res.push_back(v);
                st.pop_back();
            } else {
                auto [to, id] = g[v][it[v]++];
                if (used[id]) continue;
                used[id] = 1;
                st.push_back(to);
            }
        }
        if ((int)res.size() != m + 1) return {};
        reverse(res.begin(), res.end());
        return res;
    }

    // Euler PATH (exactly 0 or 2 odd degrees; if 2, start at an odd)
    vector<int> get_path(int start = -1) {
        int odd = 0, odd_start = -1;
        for (int i=0;i<n;i++) if (deg[i] & 1) { odd++; odd_start = i; }
        if (!(odd == 0 || odd == 2)) return {};
        if (!connected_ignoring_isolated(start)) return {};
        if (odd == 2 && (start < 0 || (deg[start] % 2 == 0))) start = odd_start;
        return hierholzer(start);
    }

    // Euler CYCLE (all degrees even) — STRICT: no isolated vertices allowed
    vector<int> get_cycle(int start = -1) {
        for (int i=0;i<n;i++) if (deg[i] & 1) return {};
        // Forbid isolated vertices: require the cycle to include every vertex.
        for (int i=0;i<n;i++) if (deg[i] == 0) return {};
        if (!connected_ignoring_isolated(start)) return {};
        auto res = hierholzer(start);
        if (res.empty()) return {};
        if (res.front() != res.back()) return {};
        return res;
    }
};  

/*** ===================== DIRECTED EULER ====================== ***/
// 0-indexed, allows multi-edges & self-loops
struct EulerDirected {
    int n, m;
    vector<vector<int>> g, rg; // g: forward, rg: reverse (for weak connectivity)
    vector<int> indeg, outdeg;

    // scratch
    vector<int> it;

    EulerDirected(int n=0): n(n), m(0), g(n), rg(n), indeg(n,0), outdeg(n,0) {}
    void reset(int N){ *this = EulerDirected(N); }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
        outdeg[u]++; indeg[v]++; m++;
    }

    // weak connectivity among vertices with nonzero degree (on undirected view of edges)
    bool weakly_connected_from(int start) {
        if (m == 0) return true;
        int s = start;
        if (s < 0 || (indeg[s] + outdeg[s] == 0)) {
            s = -1;
            for (int i=0;i<n;i++) if (indeg[i]+outdeg[i] > 0) { s = i; break; }
            if (s == -1) return true;
        }
        vector<char> vis(n, 0);
        stack<int> st; st.push(s); vis[s]=1;
        int seen = 0, need = 0;
        for (int i=0;i<n;i++) if (indeg[i]+outdeg[i] > 0) need++;
        while(!st.empty()){
            int u = st.top(); st.pop();
            if (indeg[u]+outdeg[u] > 0) seen++;
            for (int v: g[u]) if (!vis[v]) vis[v]=1, st.push(v);
            for (int v: rg[u]) if (!vis[v]) vis[v]=1, st.push(v);
        }
        return seen == need;
    }

    vector<int> hierholzer(int start) {
        if (m == 0) return {start < 0 ? 0 : start};
        it.assign(n, 0);
        vector<int> st, res;
        int s = start;
        if (s < 0 || (indeg[s]+outdeg[s] == 0)) {
            for (int i=0;i<n;i++) if (outdeg[i] > 0){ s=i; break; }
        }
        st.push_back(s);
        while(!st.empty()){
            int v = st.back();
            if (it[v] == (int)g[v].size()){
                res.push_back(v);
                st.pop_back();
            } else {
                int to = g[v][it[v]++];
                st.push_back(to);
            }
        }
        if ((int)res.size() != m + 1) return {};
        reverse(res.begin(), res.end());
        return res;
    }

    // Euler PATH:
    // exactly one vertex with out-in = +1 (start), one with in-out = +1 (end), others equal
    vector<int> get_path(int start = -1) {
        int start_cand = -1, end_cand = -1;
        for (int i=0;i<n;i++){
            int d = outdeg[i] - indeg[i];
            if (d == 1) {
                if (start_cand != -1) return {};
                start_cand = i;
            } else if (d == -1) {
                if (end_cand != -1) return {};
                end_cand = i;
            } else if (d != 0) return {};
        }
        if (start < 0) start = (start_cand != -1 ? start_cand : -1);
        if (!weakly_connected_from(start)) return {};
        auto res = hierholzer(start);
        if (res.empty()) return {};
        return res;
    }

    // Euler CYCLE: in[v] == out[v] for all v — STRICT: no isolated vertices allowed
    vector<int> get_cycle(int start = -1) {
        for (int i=0;i<n;i++) if (indeg[i] != outdeg[i]) return {};
        // Forbid isolated vertices (require every vertex to be part of the tour)
        for (int i=0;i<n;i++) if (indeg[i] + outdeg[i] == 0) return {};
        if (!weakly_connected_from(start)) return {};
        auto res = hierholzer(start);
        if (res.empty()) return {};
        if (res.front() != res.back()) return {};
        return res;
    }
};

/*** ========================= DEMO =========================== ***/
// Build your graph, then call get_path() or get_cycle().
// Returned sequence is 0-indexed vertices. Print +1 if you need 1-indexed.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ------- Undirected sample -------
    {
        EulerUndirected EU(3);
        EU.add_edge(0,1);
        EU.add_edge(1,2);
        EU.add_edge(2,0);
        auto cyc = EU.get_cycle();        // exists
        auto path = EU.get_path();        // also exists (a cycle is a path)
        if (!cyc.empty()) {
            cout << "Undirected cycle: ";
            for (int v: cyc) cout << v+1 << ' '; cout << "\n";
        } else cout << "Undirected cycle: IMPOSSIBLE\n";
        if (!path.empty()) {
            cout << "Undirected path:  ";
            for (int v: path) cout << v+1 << ' '; cout << "\n";
        } else cout << "Undirected path: IMPOSSIBLE\n";
    }

    // ------- Directed sample -------
    {
        EulerDirected ED(3);
        ED.add_edge(0,1);
        ED.add_edge(1,2);
        ED.add_edge(2,0);
        auto cyc = ED.get_cycle();  // exists
        auto path = ED.get_path();  // exists
        if (!cyc.empty()) {
            cout << "Directed cycle:   ";
            for (int v: cyc) cout << v+1 << ' '; cout << "\n";
        } else cout << "Directed cycle: IMPOSSIBLE\n";
        if (!path.empty()) {
            cout << "Directed path:    ";
            for (int v: path) cout << v+1 << ' '; cout << "\n";
        } else cout << "Directed path: IMPOSSIBLE\n";
    }

    return 0;
}

/*** ----------------------- NOTES & TIPS ------------------------
 * Undirected:
 *  - Euler path iff 0 or 2 odd-degree vertices, and non-isolated part connected.
 *  - Euler cycle (STRICT here) iff all degrees even, no isolated vertices, and connected.
 *
 * Directed:
 *  - Euler path iff exactly one vertex has out-in = +1 (start), one has in-out = +1 (end), others equal,
 *    and all nonzero-degree vertices are weakly connected.
 *  - Euler cycle (STRICT here) iff in[v] == out[v] for all v, no isolated vertices, and weakly connected.
 *
 * Complexity: O(n + m). Sequence length is m+1.
 * -------------------------------------------------------------- */
