#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;

class Node {
   public:
	string city;
	int gas; // [deciliter]
	int dist;

	Node(const string& city, const int& gas, const int& dist)
		: city(city), gas(gas), dist(dist) {};

	bool operator<(const Node& b) const {
		return (this->dist > b.dist);
	}
};

// cap [deciliter]
ll ShortestWay(const int& cap, const string& src, const string& dest, map<string, map<string, int>>& adjacents, map<string, bool>& has_station) {
	ll ans = -1;

	map<string, map<int, ll>> dist;
	dist[src][cap] = 0;
	map<string, map<int, bool>> done;
	priority_queue<Node> que;
	que.emplace(src, cap, 0);

	while (!que.empty()) {
		Node node = que.top();
		que.pop();
		if (node.city == dest) {
			ans = dist[node.city][node.gas];
			break;
		}
		done[node.city][node.gas] = true;

		for (const auto& adjacent : adjacents[node.city]) {
			int adjacent_gas = node.gas - adjacent.second;
			if (adjacent_gas < 0) continue;
			if (has_station[adjacent.first]) adjacent_gas = cap;
			if (done[adjacent.first][adjacent_gas]) continue;
			ll adjacent_dist = node.dist + adjacent.second;

			bool dismiss = false;
			for (const auto& gas_and_dist : dist[adjacent.first]) {
				if (adjacent_gas <= gas_and_dist.first and adjacent_dist >= gas_and_dist.second) dismiss = true;
			}
			if (dismiss) continue;

			dist[adjacent.first][adjacent_gas] = adjacent_dist;
			que.emplace(adjacent.first, adjacent_gas, adjacent_dist);
		}
	}

	return ans;
}

bool solve() {
	int n, m, cap;
	cin >> n >> m >> cap;
	if (n == 0) return false;
	string src, dest;
	cin >> src >> dest;
	map<string, map<string, int>> adjacents;
	for (int i = 0; i < n; i++) {
		string c1, c2;
		int d;
		cin >> c1 >> c2 >> d;
		adjacents[c1][c2] = adjacents[c2][c1] = d;
	}
	map<string, bool> has_station;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		has_station[s] = true;
	}

	cout << ShortestWay(cap * 10, src, dest, adjacents, has_station) << endl;

	return true;
}

int main(void) {
	while (solve());
	return 0;
}