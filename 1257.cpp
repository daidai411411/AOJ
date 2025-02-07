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
	const int max_n = 10000;
	vector<int> primes = GeneratePrimes(max_n);

	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;

		int numof_representations = 0;
		for (auto p = primes.begin(); p != primes.end(); p++) {
			int sum = 0;
			for (auto q = p; q != primes.end(); q++) {
				sum += *q;
				if (sum == n) {
					numof_representations++;
					break;
				} else if (sum > n) {
					break;
				}
			}
		}

		cout << numof_representations << endl;
	}

	return 0;
}
