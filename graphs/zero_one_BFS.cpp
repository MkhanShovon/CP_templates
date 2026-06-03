vector<int> zeroOneBFS(int n, vector<vector<pair<int,int>>> &adj, int src) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    deque<int> dq;

    dist[src] = 0;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto [v, w] : adj[u]) {
            // w is 0 or 1
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;

                if (w == 0)
                    dq.push_front(v);
                else
                    dq.push_back(v);
            }
        }
    }

    return dist;
}
