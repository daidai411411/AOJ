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

vector<int> Int2Vec(int num, int l) {
	vector<int> vec(l);
	for (int i = 0; i < l; i++) {
		vec[i] = num % 10;
		num /= 10;
	}
	return vec;
}

int Vec2Int(vector<int> vec) {
	int num = 0;
	for (int i = 0; i < vec.size(); i++) {
		num *= 10;
		num += vec[vec.size() - 1 - i];
	}
	return num;
}

bool Solve(void) {
	int a0, l;
	cin >> a0 >> l;
	if (l == 0) return false;

	int a = a0;
	map<int, int> a_rev;
	a_rev[a0] = 0;
	for (int i = 1;; i++) {
		vector<int> digits = Int2Vec(a, l);
		vector<int> max_digits(digits), min_digits(digits);
		sort(max_digits.begin(), max_digits.end());
		sort(min_digits.rbegin(), min_digits.rend());
		int max = Vec2Int(max_digits), min = Vec2Int(min_digits);
		a = max - min;
		if (a_rev.find(a) != a_rev.end()) {
			cout << a_rev[a] << ' ' << a << ' ' << i - a_rev[a] << endl;
			break;
		} else {
			a_rev[a] = i;
		}
	}

	return true;
}

int main(void) {
	while (Solve());
	return 0;
}
