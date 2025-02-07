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
constexpr bool chmax(T& max, const T target) {
	if (max < target) {
		max = target;
		return true;
	}
	return false;
}

template <typename T>
constexpr bool chmin(T& min, const T target) {
	if (target < min) {
		min = target;
		return true;
	}
	return false;
}

// 正四面体数
int TetrahedralNumber(const int n) {
	return n * (n + 1) * (n + 2) / 6;
}

int main(void) {
	// dp[i] : 正整数 i を作るのに必要な正四面体数の個数の最小値
	vector<int> dp(1000000, INF);
	// dp_odd[i] : 正整数 i を作るのに必要な奇数の正四面体数の個数の最小値
	vector<int> dp_odd(1000000, INF);

	int tetra_n = 1;
	int tetra = TetrahedralNumber(tetra_n);

	for (int i = 1; i <= 1000000 - 1; i++) {
		if (i == tetra) {
			dp[i] = 1;
			if (tetra % 2 != 0) dp_odd[i] = 1;
			tetra = TetrahedralNumber(++tetra_n);
		}
		for (int j = 1;; j++) {
			int t = TetrahedralNumber(j);
			if (i - t < 1) break;
			chmin(dp[i], dp[i - t] + 1);
			if (t % 2 != 0) chmin(dp_odd[i], dp_odd[i - t] + 1);
		}
	}

	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;

		cout << dp[n] << " " << dp_odd[n] << endl;
	}

	return 0;
}
