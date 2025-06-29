#include <algorithm>
#include <array>
#include <climits>
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

/*----------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
bool ChMax(T& max, T val) {
	return (val > max) ? (max = val, true) : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/

template <typename T>
bool ChMin(T& min, T val) {
	return (val < min) ? (min = val, true) : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/

struct CombMod {
   private:
	ll m_;
	vector<ll> fact_, inv_, fact_inv_;

   public:
	CombMod(const ll m, const ll n) : m_(m), fact_(n + 1), inv_(n + 1), fact_inv_(n + 1) {
		fact_[0] = fact_[1] = inv_[1] = fact_inv_[0] = fact_inv_[1] = 1;
		for (int i = 2; i <= n; i++) {
			fact_[i] = fact_[i - 1] * i % m_;
			inv_[i] = m_ - inv_[m_ % i] * (m_ / i) % m_;
			fact_inv_[i] = fact_inv_[i - 1] * inv_[i] % m_;
		}
	}

	ll Get(const ll n, const ll k) {
		return fact_[n] * (fact_inv_[k] * fact_inv_[n - k] % m_) % m_;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------*/

struct UnionFind {
   private:
	int n_;
	int numof_unions_;
	vector<int> parent_;
	vector<int> root_size_;

   public:
	UnionFind(const int n) : n_(n), numof_unions_(n), parent_(n), root_size_(n, 1) {
		iota(parent_.begin(), parent_.end(), 0);
	}

	int Root(const int u) {
		if (parent_[u] == u) return u;
		else {
			parent_[u] = Root(parent_[u]);
			return parent_[u];
		}
	}

	void Unite(const int u, const int v) {
		int root_u = Root(u), root_v = Root(v);
		if (root_u != root_v) {
			numof_unions_--;
			parent_[root_v] = root_u;
			root_size_[root_u] += root_size_[root_v];
		}
	}

	bool Same(const int u, const int v) {
		return (Root(u) == Root(v));
	}

	int NumofUnions(void) {
		return numof_unions_;
	}

	int UnionSize(const int u) {
		return root_size_[Root(u)];
	}

	vector<vector<int>> Unions(void) {
		vector<int> indices(n_, -1);
		vector<vector<int>> unions;
		for (int i = 0; i < n_; i++) {
			if (indices[Root(i)] == -1) {
				indices[Root(i)] = unions.size();
				unions.emplace_back(1, i);
			} else {
				unions[indices[Root(i)]].emplace_back(i);
			}
		}
		return unions;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------*/

int main(void) {
	int a, b;
	cin >> a >> b;
	cout << ChMax(a, b) << ' ' << a << ' ' << endl;
	return 0;
}
