#include <algorithm>
#include <bitset>
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

bool IsTop(const vector<int>& over, const int disks, const int disk) {
	return !(over[disk] & disks);
}

void chmax(int& a, const int b) {
	if (a < b) a = b;
}

int CountRemovableDisksRec(const vector<int>& over, const vector<int>& c, const int disks, vector<int>& memo) {
	if (memo[disks] >= 0) return memo[disks];

	int ans = 0;

	for (int i = 0; i < over.size(); i++) {
		if (!(disks & (1 << i)) || !IsTop(over, disks, i)) continue;
		for (int j = 0; j < i; j++) {
			if (!(disks & (1 << j)) || !IsTop(over, disks, j)) continue;
			if (c[i] != c[j]) continue;
			chmax(ans, CountRemovableDisksRec(over, c, disks ^ ((1 << i) | (1 << j)), memo) + 2);
		}
	}

	memo[disks] = ans;
	return ans;
}

int CountRemovableDisks(const vector<int>& over, const vector<int>& c, const int disks) {
	vector<int> memo(1 << (over.size()), -1);
	return CountRemovableDisksRec(over, c, disks, memo);
}

bool Solve() {
	int n;
	cin >> n;
	if (n == 0) return false;
	vector<int> x(n), y(n), r(n), c(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> r[i] >> c[i];
	}

	vector<int> over(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) < (r[i] + r[j]) * (r[i] + r[j])) {
				over[i] |= 1 << j;
			}
		}
	}

	int ans = CountRemovableDisks(over, c, (1 << n) - 1);
	cout << ans << endl;

	return true;
}

int main(void) {
	while (Solve());
	return 0;
}
