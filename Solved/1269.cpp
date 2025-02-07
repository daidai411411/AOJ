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

#define N_MAX (1120)
#define K_MAX (14)

using namespace std;
using ll = long long;

vector<int> GeneratePrimes(void) {
	vector<int> primes;
	vector<bool> is_prime(N_MAX + 1, true);

	for (int i = 2; i <= N_MAX; i++) {
		if (is_prime[i]) {
			primes.push_back(i);
			for (int j = 2 * i; j <= N_MAX; j += i) is_prime[j] = false;
		}
	}

	return primes;
}

int main(void) {
	vector<int> primes = GeneratePrimes();

	// dp[n][k] : n を互いに異なる k 個の素数の和で表す方法の数
	vector<vector<ll>> dp(N_MAX + 1, vector<ll>(K_MAX + 1, 0LL));
	dp[0][0] = 1LL;

	for (const int p : primes) {
		vector<vector<ll>> dp_add(N_MAX + 1, vector<ll>(K_MAX + 1, 0LL));
		for (int n = 0; n + p <= N_MAX; n++) {
			for (int k = 0; k + 1 <= K_MAX; k++) {
				dp_add[n + p][k + 1] = dp[n][k];
			}
		}

		for (int n = 0; n <= N_MAX; n++) {
			for (int k = 0; k <= K_MAX; k++) {
				dp[n][k] += dp_add[n][k];
			}
		}
	}

	while (true) {
		int N, K;
		cin >> N >> K;
		if (N == 0) break;
		cout << dp[N][K] << endl;
	}

	return 0;
}
