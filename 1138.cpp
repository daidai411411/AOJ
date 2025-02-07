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

struct Node {
	int city;
	int tickets;

	Node(const int city, const int tickets)
		: city(city), tickets(tickets) {};

	bool operator<(const Node& node) const {
		if (this->city != node.city) return this->city < node.city;
		else return this->tickets < node.tickets;
	}
};

struct QueueItem {
	Node node;
	double shortest_time;

	QueueItem(const Node node, const double shortest_time)
		: node(node), shortest_time(shortest_time) {};

	bool operator<(const QueueItem& queue_item) const {
		return this->shortest_time > queue_item.shortest_time;
	}
};

void Solve(const int& n, const int& dep, const int& dst, const map<int, int>& numof_horses, const vector<map<int, int>>& distances) {
	double shortest_time_to_dst = -1.0;

	map<Node, double> shortest_time;
	priority_queue<QueueItem> queue;

	shortest_time[Node(dep, (1 << n) - 1)] = 0.0;
	queue.push(QueueItem(Node(dep, (1 << n) - 1), 0.0));
	while (!queue.empty()) {
		Node current = queue.top().node;
		queue.pop();

		if (current.city == dst) {
			shortest_time_to_dst = shortest_time[current];
			break;
		}

		for (const auto& entry : distances[current.city]) {
			int adjacent_city = entry.first, distance = entry.second;
			for (int ticket = 1 << (n - 1); ticket > 0; ticket >>= 1) {
				if ((current.tickets & ticket) == 0) continue;
				Node adjacent(adjacent_city, current.tickets ^ ticket);
				double adjacent_shortest_time = shortest_time[current] + (double)distance / numof_horses.at(ticket);
				if (shortest_time.find(adjacent) != shortest_time.end() and shortest_time[adjacent] <= adjacent_shortest_time) continue;
				shortest_time[adjacent] = adjacent_shortest_time;
				queue.push(QueueItem(adjacent, adjacent_shortest_time));
			}
		}
	}

	if (shortest_time_to_dst == -1.0) cout << "Impossible" << endl;
	else cout << shortest_time_to_dst << endl;
}

int main(void) {
	cout << fixed << setprecision(3);
	while (true) {
		int n, m, p, a, b;
		cin >> n >> m >> p >> a >> b;
		if (n == 0) break;
		a--;
		b--;
		map<int, int> numof_horses;
		for (int ticket = 1 << (n - 1); ticket > 0; ticket >>= 1) cin >> numof_horses[ticket];
		vector<map<int, int>> distances(m);
		for (int i = 0; i < p; i++) {
			int x, y, z;
			cin >> x >> y >> z;
			x--;
			y--;
			distances[x][y] = distances[y][x] = z;
		}
		Solve(n, a, b, numof_horses, distances);
	}
	return 0;
}
