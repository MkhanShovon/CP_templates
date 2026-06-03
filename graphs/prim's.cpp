#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::vector;

long long prim(const vector<vector<pair<int, int>>> &neighbors) {
	const int n = neighbors.size();  // just a shorthand

	long long min_cost = 0;
	vector<long long> dist(n, std::numeric_limits<long long>().max());
	dist[0] = 0;
	std::priority_queue<pair<long long, int>> q;
	q.push({0, 0});
	vector<bool> visited(n);
	int added = 0;
	while (added < n) {
		if (q.empty()) { return -1; }
		auto [curr_cost, v] = q.top();
		q.pop();
		curr_cost *= -1;
		if (dist[v] < curr_cost) { continue; }

		added++;
		visited[v] = true;
		min_cost += curr_cost;
		for (auto &[next, n_cost] : neighbors[v]) {
			if (!visited[next] && n_cost < dist[next]) {
				dist[next] = n_cost;
				q.push({-n_cost, next});
			}
		}
	}

	return min_cost;
}

int main() {
	int city_num;
	int road_num;
	std::cin >> city_num >> road_num;

	vector<vector<pair<int, int>>> neighbors(city_num);
	for (int r = 0; r < road_num; r++) {
		int a, b;
		int cost;
		std::cin >> a >> b >> cost;
		neighbors[--a].push_back({--b, cost});
		neighbors[b].push_back({a, cost});
	}

	long long min_cost = prim(neighbors);
	if (min_cost == -1) {
		cout << "IMPOSSIBLE" << endl;
	} else {
		cout << min_cost << endl;
	}
}
