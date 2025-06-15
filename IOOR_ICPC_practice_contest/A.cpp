#include <algorithm>
#include <array>
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;

template <typename T>
bool ChMax(T& max, T val) {
	return (val > max) ? (max = val, true) : false;
}

bool Solve(void) {
	int n, m;
	cin >> n >> m;
	if (n == 0) return false;
	vector<int> sum(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int p;
            cin >> p;
            sum[j] += p;
        }
    }

    int max = 0;
    for (int i : sum) ChMax(max, i);

    cout << max << endl;

	return true;
}

int main(void) {
	while (Solve());
	return 0;
}
