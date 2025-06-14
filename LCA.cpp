#include <bits/stdc++.h>
using namespace std;
int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;
vector<int> depth;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
        {    
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    // debug(root);
    tin.resize(n);
    tout.resize(n);
    depth.assign(n, 0);
    timer = 0;
    l = ceil(log2(n));
    // debug(l, n);
    up.assign(n, vector<int>(l + 1));
    depth[root] = 1;
    // debug(root, l, n);
    dfs(root, root);
}