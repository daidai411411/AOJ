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

int main() {
	while (true) {
		// input
		int offered_fuel = 0;
		cin >> offered_fuel;
		if (offered_fuel == 0) break;

		// calc
		int request_fuel = 0;
		for (int n1 = 0;; n1++) {
			int fuel1 = n1 * n1 * n1;
			if (offered_fuel < fuel1) break;

			for (int n2 = 0;; n2++) {
				int fuel2 = n2 * (n2 + 1) * (n2 + 2) / 6;
				int sum = fuel1 + fuel2;
				if (offered_fuel < sum) break;

				if (request_fuel < sum) request_fuel = sum;
			}
		}

		// output
		cout << request_fuel << endl;
	}

	return 0;
}
