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

vector<int> GeneratePrimes(int max) {
	vector<bool> is_prime_list(max, true);
	vector<int> primes;
	is_prime_list[0] = is_prime_list[1] = false;

	for (int i = 2; i <= max; i++) {
		if (!is_prime_list[i]) continue;
		primes.push_back(i);
		for (int j = 2 * i; j <= max; j += i) {
			is_prime_list[j] = false;
		}
	}

	return primes;
}

int main() {
	vector<int> primes = GeneratePrimes(50000);

	while (true) {
		int m, a, b;
		cin >> m >> a >> b;
		if (m == 0 && a == 0 && b == 0) break;

		int max = 0, max_p = 0, max_q = 0;
		for (auto p = primes.begin(); p != primes.end() && *p <= m; p++) {
			for (auto q = p; q != primes.end() && *p * *q <= m && a * *q <= b * *p; q++) {
				if (max < *p * *q) {
					max = *p * *q;
					max_p = *p;
					max_q = *q;
				}
			}
		}

		cout << max_p << " " << max_q << endl;
	}

	return 0;
}
