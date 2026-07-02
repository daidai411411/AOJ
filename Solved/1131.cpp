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

struct Frac {
	// p/q
	int p, q;

	static Frac Reduce(const Frac& f) {
		int g = gcd(f.p, f.q);
		return Frac{f.p / g, f.q / g};
	}

	Frac Reduce(void) const {
		int g = gcd(this->p, this->q);
		return Frac{this->p / g, this->q / g};
	}

	Frac operator-(const Frac& t) const {
		return Frac{this->p * t.q - t.p * this->q, this->q * t.q}.Reduce();
	}

	auto operator<=>(const Frac& t) const {
		return (this->p * t.q) <=> (t.p * this->q);
	}

	bool operator==(const Frac& t) const {
		return (*this <=> t) == 0;
	}

	auto operator<=>(const int& t) const {
		return (*this <=> Frac{t, 1});
	}

	bool operator==(const int& t) const {
		return (*this <=> t) == 0;
	}
};

void Dfs(Frac f, int a, int n, int s, int& ans) {
    // cout << f.p << "/" << f.q << "\t" << a << "\t" << n << "\t" << s << "\t" << ans << endl;
    if (n == 0) return;
	for (int i = s; i <= a; i++) {
		Frac remainder = f - Frac{1, i};
		if (remainder < 0) continue;
		if (remainder == 0) {
			ans++;
			continue;
		}
		if (remainder > Frac{n - 1, i}) break;
        Dfs(remainder, a / i, n - 1, i, ans);
	}
}

void Solve(int p, int q, int a, int n) {
	int ans = 0;
	Dfs(Frac{p, q}.Reduce(), a, n, 1, ans);
	cout << ans << endl;
	return;
}

int main(void) {
	int p, q, a, n;
	while (true) {
		cin >> p >> q >> a >> n;
		if (p == 0) break;
		Solve(p, q, a, n);
	}
	return 0;
}

/*

1/2 = 1/7 + 1/7 + 1/7 + 1/14 (積=4802)

1/3 = 1/7 + 1/7 + 1/21 (積=1029)

2/3 = 1/5 + 1/5 + 1/5 + 1/15 (積=1875)

1/6 = 1/10 + 1/15

5/6 = 1/2 + 1/3

*/

/*
2 3 120 3

2/3 = 1/3 + 1/3
4/6 = 3/6 + 1/6
4/6 = 2/6 + 1/6 + 1/6
8/12 = 3/12 + 3/12 + 2/12


2 3 300 3

2/3 = 1/3 + 1/3
4/6 = 3/6 + 1/6
4/6 = 2/6 + 1/6 + 1/6
8/12 = 6/12 + 1/12 + 1/12
8/12 = 4/12 + 3/12 + 1/12
8/12 = 3/12 + 3/12 + 2/12
20/30 = 15/30 + 3/30 + 2/30


2 3 299 3

2/3 = 1/3 + 1/3
4/6 = 3/6 + 1/6
4/6 = 2/6 + 1/6 + 1/6
8/12 = 6/12 + 1/12 + 1/12
8/12 = 4/12 + 3/12 + 1/12
8/12 = 3/12 + 3/12 + 2/12


2 3 12 3

2/3 = 1/3 + 1/3
4/6 = 3/6 + 1/6


2 1 200 5
                                p/q     a       ok
1/1 + 1/1                       2       1       o
1/1 + 1/2 + 1/2                 2       4       o
1/1 + 1/2 + 1/3 + 1/3           7/6     18      x
1/1 + 1/2 + 1/3 + 1/4           25/12   24      x
1/1 + 1/2 + 1/3 + 1/5           61/30   30      x
1/1 + 1/2 + 1/3 + 1/6           2       36      o
1/1 + 1/2 + 1/4 + 1/4           2       32      o
1/1 + 1/3 + 1/3 + 1/3           2       27      o
1/2 + 1/2 + 1/2 + 1/2           2       16      o
1/2 + 1/2 + 1/2 + 1/3 + 1/6     2       144     o
1/2 + 1/2 + 1/2 + 1/4 + 1/4     2       128     o
1/2 + 1/2 + 1/3 + 1/3 + 1/3     2       108     o
1/3 + 1/3 + 1/3 + 1/3 + 1/3     5/3     243     x

*/
