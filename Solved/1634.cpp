#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
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

void CalcMeasurableWeights(set<ll>& measurable_weights, const vector<ll>& w, ll weight = 0, int i = 0) {
	if (i == w.size()) return;

	for (int j = -1; j <= 1; j++) {
		if (i == 0 and j == -1) continue;
		ll new_weight = weight + j * w[i];
		measurable_weights.insert(abs(new_weight));
		CalcMeasurableWeights(measurable_weights, w, new_weight, i + 1);
	}
}

set<ll> CalcMeasurableWeights(const vector<ll>& w) {
	set<ll> measurable_weights;
	CalcMeasurableWeights(measurable_weights, w);
	return measurable_weights;
}

vector<ll> CalcUnmeasurableChemicals(const vector<ll>& a, const set<ll>& measurable_weights) {
	vector<ll> unmeasurable_chemicals;
	for (ll i : a) {
		if (measurable_weights.find(i) == measurable_weights.end()) unmeasurable_chemicals.emplace_back(i);
	}
	return unmeasurable_chemicals;
}

vector<set<ll>> CalcWishLists(const set<ll>& measurable_weights, const vector<ll>& unmeasurable_chemicals) {
	vector<set<ll>> wish_lists(unmeasurable_chemicals.size());
	for (int i = 0; i < unmeasurable_chemicals.size(); i++) {
		for (ll j : measurable_weights) {
			wish_lists[i].insert(abs(unmeasurable_chemicals[i] - j));
			wish_lists[i].insert(unmeasurable_chemicals[i] + j);
		}
	}
	return wish_lists;
}

set<ll> CalcCommonWishList(const vector<set<ll>>& wish_lists) {
	set<ll> common_wish_list{wish_lists.front()};
	for (int i = 1; i < wish_lists.size(); i++) {
		set<ll> intersection;
		set_intersection(common_wish_list.begin(), common_wish_list.end(), wish_lists[i].begin(), wish_lists[i].end(), inserter(intersection, intersection.end()));
        common_wish_list = intersection;
	}
    return common_wish_list;
}

ll Solve(int n, int m, vector<ll>& a, vector<ll>& w) {
	set<ll> measurable_weights = CalcMeasurableWeights(w);
	vector<ll> unmeasurable_chemicals = CalcUnmeasurableChemicals(a, measurable_weights);
	if (unmeasurable_chemicals.empty()) return 0;
	vector<set<ll>> wish_lists = CalcWishLists(measurable_weights, unmeasurable_chemicals);
	set<ll> common_wish_list = CalcCommonWishList(wish_lists);
	if (common_wish_list.empty()) return -1;
	return *(common_wish_list.begin());
}

int main(void) {
	while (true) {
		int n, m;
		cin >> n >> m;
		vector<ll> a(n), w(m);
		for (ll& i : a) cin >> i;
		for (ll& i : w) cin >> i;
		if (n == 0) break;
		cout << Solve(n, m, a, w) << endl;
	}
	return 0;
}

/*
4 2
9 2 7 11
2 9

可能: 0 2 7 9 11
不能: なし
解答: 0
*/

/*
6 2
7 3 6 12 16 9
2 9

可能: 0 2 7 9 11
不能: 3 6 12 16
解答: 5
*/

/*
5 2
7 3 6 12 17
2 9

可能: 0 2 7 9 11
不能: 3 6 12 17
解答: -1
*/

/*
7 5
15 21 33 48 51 75 111
36 54 57 93 113

可能: 0 1 2 3 13 16 17 18 19 20 21 23 33 34 36 37 38 39 41 53 54 55 56 57 59 60 70 72 73 74 75 77 80 90 91 92 93 95 96 110 111 113 114 116 126 127 129 131 132 134 146 147 149 150 152 167 168 170 173 183 185 186 188 203 204 206 209 224 227 239 240 242 245 260 263 281 296 299 317 353
不能: 15 48 51
解答: 5
*/
