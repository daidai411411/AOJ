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

// 命令
// 0: 「直進」命令
// 1: 「右折」命令
// 2: 「反転」命令
// 3: 「左折」命令
// 4: 「停止」命令

// 方向
// 0: 右
// 1: 下
// 2: 左
// 3: 上

int main(void) {
	const int directions[4][2]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

	while (true) {
		int W, H, costs[4];
		cin >> W >> H;
		if (W == 0) break;
		vector<vector<int>> commands(H, vector<int>(W));
		for (vector<int>& row : commands) {
			for (int& sqr : row) cin >> sqr;
		}
		for (int& cost : costs) cin >> cost;

		int count_done_goal = 0;
		int recent_done_r = 0, recent_done_c = 0, recent_done_d = 0;
		vector<vector<vector<int>>> distances(H, vector<vector<int>>(W, vector<int>(4, INF)));
		distances[recent_done_r][recent_done_c][recent_done_d] = 0;
		vector<vector<vector<bool>>> done(H, vector<vector<bool>>(W, vector<bool>(4, false)));
		done[recent_done_r][recent_done_c][recent_done_d] = true;
		while (true) {
			for (int cmd = 0; cmd < 4; cmd++) {
				int turn_to = (recent_done_d + cmd) % 4;
				int adjacent_r = recent_done_r + directions[turn_to][0];
				int adjacent_c = recent_done_c + directions[turn_to][1];
				if (adjacent_r < 0 || H <= adjacent_r || adjacent_c < 0 || W <= adjacent_c || done[adjacent_r][adjacent_c][turn_to]) continue;
				int new_distance = distances[recent_done_r][recent_done_c][recent_done_d];
				if (cmd != commands[recent_done_r][recent_done_c]) new_distance += costs[cmd];
				chmin(distances[adjacent_r][adjacent_c][turn_to], new_distance);
			}

			int min_distance = INF, min_r, min_c, min_d;
			for (int r = 0; r < H; r++) {
				for (int c = 0; c < W; c++) {
					for (int d = 0; d < 4; d++) {
						if (done[r][c][d]) continue;
						if (chmin(min_distance, distances[r][c][d])) {
							min_r = r;
							min_c = c;
							min_d = d;
						}
					}
				}
			}
			done[min_r][min_c][min_d] = true;
			recent_done_r = min_r;
			recent_done_c = min_c;
			recent_done_d = min_d;

			if (recent_done_r == H - 1 && recent_done_c == W - 1) {
				count_done_goal++;
				if (count_done_goal == 2) break;
			}
		}

		int min_distance_goal = INF;
		for (int d = 0; d < 4; d++) {
			chmin(min_distance_goal, distances[H - 1][W - 1][d]);
		}

		cout << min_distance_goal << endl;
	}

	return 0;
}
