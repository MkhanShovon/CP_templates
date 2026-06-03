#include<bits/stdc++.h> 
using namespace std;    

using ll = long long;
vector<int> adj[100005];
int indeg[100005];
vector<int> topo_sort(int n) {
    vector<int> res;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        res.push_back(node);
        for (auto child : adj[node]) {
            indeg[child]--;
            if (indeg[child] == 0) {
                q.push(child);
            }
        }
    }
    if ((int)res.size() != n) {
        // Graph has a cycle
        return {};
    }
    return res;
}