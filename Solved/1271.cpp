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

// 現在の演算回数 c と演算履歴 history から x^target を upper_limit 回の演算以内で計算できるならば true を返す。そうでなければ false を返す。
bool Dfs(const int c, vector<int>& history, const int target, int& upper_limit) {
	if (history[c] == target) return true;
	if (c == upper_limit) return false;

	int max = *max_element(history.begin(), history.begin() + c + 1);
	if ((max << (upper_limit - c)) < target) return false;

	for (int i = 0; i <= c; i++) {
		if (i != c and history[i] == history[c]) return false;

		history[c + 1] = history[i] + history[c];
		if (Dfs(c + 1, history, target, upper_limit)) return true;

		if (history[i] < history[c]) {
			history[c + 1] = history[c] - history[i];
			if (Dfs(c + 1, history, target, upper_limit)) return true;
		}
	}
	return false;
}

int Solve(const int n) {
	// 反復深化深さ優先探索
	for (int upper_limit = 0;; upper_limit++) {
		vector<int> history(upper_limit + 1, {1}); // i 回目の演算で x^(history[i]) が得られたという履歴
		if (Dfs(0, history, n, upper_limit)) return upper_limit;
	}
}

int main(void) {
	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;
		cout << Solve(n) << endl;
	}
	return 0;
}