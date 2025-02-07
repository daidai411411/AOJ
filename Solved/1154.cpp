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

vector<int> GeneratePrimes(const int max) {
	vector<int> primes;
	vector<bool> isnt_prime(max, false);

	for (int i = 7; i <= max; i += 7) {
		for (int j = i - 1; j <= i + 1 && j <= max; j += 2) {
			if (isnt_prime[j]) continue;
			primes.push_back(j);
			for (int k = j; k <= max; k += j) {
				isnt_prime[k] = true;
			}
		}
	}

	return primes;
}

int main() {
	const int max = 300000 - 1;
	vector<int> primes = GeneratePrimes(max);

	while (true) {
		int n;
		cin >> n;
		if (n == 1) break;

		cout << n << ":";

		for (int p : primes) {
			if (n % p == 0) cout << " " << p;
		}

		cout << endl;
	}

	return 0;
}
