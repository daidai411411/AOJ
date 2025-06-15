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

bool Solve(void) {
	int m, n, p;
	cin >> m >> n >> p;
	if (m == 0) return false;
    set<int> infected;
	infected.insert(p);
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
        if (infected.find(a) == infected.end() and infected.find(b) == infected.end()) continue;
        infected.insert(a);
        infected.insert(b);
	}

    int ans = infected.size();

    cout << ans << endl;

	return true;
}

int main(void) {
	while (Solve());
	return 0;
}
