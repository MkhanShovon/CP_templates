const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

/*
    Computes shortest paths from a source vertex s.
    adj: adjacency list where adj[v] = { (to, weight), ... }
    d[v]: shortest distance from s to v
    p[v]: parent of v in the shortest-path tree
*/
void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    
    // Initialize distance array with INF, parent with -1
    d.assign(n, INF);
    p.assign(n, -1);

    // u[v] = true means vertex v is already processed (finalized)
    vector<bool> u(n, false);

    // Distance to the source is zero
    d[s] = 0;

    // We will process exactly n vertices (or stop early)
    for (int i = 0; i < n; i++) {

        // Pick the unprocessed vertex v with smallest distance d[v]
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        // If the smallest distance is INF, no reachable vertices remain
        if (d[v] == INF)
            break;

        // Mark vertex v as processed — we now know its shortest path
        u[v] = true;

        // Relax all outgoing edges from v
        for (auto edge : adj[v]) {
            int to = edge.first;      // neighboring vertex
            int len = edge.second;    // weight of edge v -> to

            // If a shorter path through v is found, update it
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;            // track the parent for path reconstruction
            }
        }
    }
}
