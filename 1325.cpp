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
#include <string>
#include <vector>

using namespace std;
using ll = long long;

bool isPrime(int m, int n) {
	for (int d = 0; d <= 142; d++) {
		for (int e = 0; e <= 142; e++) {
			int d2pe2 = d * d + e * e;
			if (d2pe2 <= 1 || 20000 <= d2pe2 || d == m && e == n || d == -n && e == m || d == -m && e == -n || d == n && e == -m) continue;

			if ((d * m + e * n) % d2pe2 == 0 && (d * n - e * m) % d2pe2 == 0) return false;
		}
	}

	return true;
}

int main() {
	int numof_data;
	cin >> numof_data;

	for (int data = 0; data < numof_data; data++) {
		int m, n;
		cin >> m >> n;

		if (isPrime(m, n)) {
			cout << "P" << endl;
		} else {
			cout << "C" << endl;
		}
	}

	return 0;
}
