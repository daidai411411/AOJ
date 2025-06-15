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
    int n, p;
    cin >> n >> p;
    if (n == 0) return false;

    vector<int> stones(n);
    int bowl = p, winner;
    for (int i = 0;; i = (i + 1) % n) {
        if (bowl > 0) {
            bowl--;
            stones[i]++;
            if (stones[i] == p) {
                winner = i;
                break;
            }
        } else {
            bowl += stones[i];
            stones[i] = 0;
        }
    }

    cout << winner << endl;

	return true;
}

int main(void) {
	while (Solve());
	return 0;
}
