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

#define INF (1000000000)

using namespace std;
using ll = long long;

template <typename T>
constexpr bool chmin(T& min, const T target) {
	if (target < min) {
		min = target;
		return true;
	}
	return false;
}

// face
// 0: top
// 1: bottom
// 2: north
// 3: south
// 4: east
// 5: west

// direction
// 0: north
// 1: south
// 2: east
// 3: west

class Index {
   public:
	int phase{0}, i{0}, j{0};
	string state{"012345"};
};

string Roll(string state, const int direction) {
	const int R[4][6]{
		{2, 3, 1, 0, 4, 5},
		{3, 2, 0, 1, 4, 5},
		{4, 5, 2, 3, 1, 0},
		{5, 4, 2, 3, 0, 1},
	};

	string rolled{"012345"};
	for (int f = 0; f < 6; f++) rolled[R[direction][f]] = state[f];
	return rolled;
}

int main(void) {
	const int directions[4][2]{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

	while (true) {
		int width, depth;
		string visits;
		cin >> width >> depth;
		if (width == 0) break;
		vector<vector<char>> bed(width, vector<char>(depth));
		Index start{0, 0, 0, "rcgmby"};
		for (int j = 0; j < depth; j++) {
			string row;
			cin >> row;
			for (int i = 0; i < width; i++) {
				bed[i][j] = row[i];
				if (bed[i][j] == '#') {
					start.i = i;
					start.j = j;
					bed[i][j] = 'w';
				}
			}
		}
		cin >> visits;

		cout << flush;

		ll min_distance_to_goal = INF;
		vector<vector<vector<map<string, ll>>>> distance(6, vector<vector<map<string, ll>>>(width, vector<map<string, ll>>(depth)));
		distance[start.phase][start.i][start.j][start.state] = 0;
		queue<Index> tobe_search;
		tobe_search.push(start);
		while (!tobe_search.empty()) {
			Index current = tobe_search.front();
			tobe_search.pop();

			for (int d = 0; d < 4; d++) {
				Index adjacent{
					current.phase + (bed[current.i][current.j] == 'w' ? 0 : 1),
					current.i + directions[d][0],
					current.j + directions[d][1],
					Roll(current.state, d),
				};

				if (adjacent.phase == 6 ||
					adjacent.i < 0 || width <= adjacent.i || adjacent.j < 0 || depth <= adjacent.j ||
					bed[adjacent.i][adjacent.j] == 'k' ||
					(bed[adjacent.i][adjacent.j] != 'w' && bed[adjacent.i][adjacent.j] != visits[adjacent.phase]) ||
					(bed[adjacent.i][adjacent.j] != 'w' && bed[adjacent.i][adjacent.j] != adjacent.state[0]) ||
					distance[adjacent.phase][adjacent.i][adjacent.j].find(adjacent.state) != distance[adjacent.phase][adjacent.i][adjacent.j].end())
				{
					continue;
				}

				distance[adjacent.phase][adjacent.i][adjacent.j][adjacent.state] = distance[current.phase][current.i][current.j][current.state] + 1;
				tobe_search.push(adjacent);
			}

			if (bed[current.i][current.j] == visits[5]) chmin(min_distance_to_goal, distance[current.phase][current.i][current.j][current.state]);
		}

		if (min_distance_to_goal != INF) cout << min_distance_to_goal << endl;
		else cout << "unreachable" << endl;
	}

	return 0;
}
