#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g;
vector<int> in, out, path;

void dfs(int node) {
	while (!g[node].empty()) {
		int son = g[node].back();
		g[node].pop_back();
		dfs(son);
	}
	path.push_back(node);
}

int main() {
	cin >> n >> m;

	g.resize(n + 1);
	in.resize(n + 1);
	out.resize(n + 1);

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		out[x]++;
		in[y]++;
	}

	bool flag = true;
	for (int node = 2; node < n && flag; node++) {
		if (in[node] != out[node]) { flag = false; }
	}
	if (out[1] != in[1] + 1 || out[n] != in[n] - 1 || !flag) {
		cout << "IMPOSSIBLE";
		return 0;
	}

	dfs(1);

	reverse(path.begin(), path.end());
	if (path.size() != m + 1 || path.back() != n) {
		cout << "IMPOSSIBLE";
	} else {
		for (auto node : path) { cout << node << ' '; }
	}
}
