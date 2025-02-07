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

using namespace std;
using ll = long long;

// 各回転の回転行列
const int R[24][3][3]{
	// +x -> +x 固定, +x 周りに 90°ずつ回転
	{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
	},
	{
		{1, 0, 0},
		{0, 0, -1},
		{0, 1, 0},
	},
	{
		{1, 0, 0},
		{0, -1, 0},
		{0, 0, -1},
	},
	{
		{1, 0, 0},
		{0, 0, 1},
		{0, -1, 0},
	},
	// +x -> -x 固定, -x 周りに 90°ずつ回転
	{
		{-1, 0, 0},
		{0, 0, 1},
		{0, 1, 0},
	},
	{
		{-1, 0, 0},
		{0, 1, 0},
		{0, 0, -1},
	},
	{
		{-1, 0, 0},
		{0, 0, -1},
		{0, -1, 0},
	},
	{
		{-1, 0, 0},
		{0, -1, 0},
		{0, 0, 1},
	},
	// +x -> +y 固定, +y 周りに 90°ずつ回転
	{
		{0, 0, 1},
		{1, 0, 0},
		{0, 1, 0},
	},
	{
		{0, 1, 0},
		{1, 0, 0},
		{0, 0, -1},
	},
	{
		{0, 0, -1},
		{1, 0, 0},
		{0, -1, 0},
	},
	{
		{0, -1, 0},
		{1, 0, 0},
		{0, 0, 1},
	},
	// +x -> -y 固定, -y 周りに 90°ずつ回転
	{
		{0, 1, 0},
		{-1, 0, 0},
		{0, 0, 1},
	},
	{
		{0, 0, -1},
		{-1, 0, 0},
		{0, 1, 0},
	},
	{
		{0, -1, 0},
		{-1, 0, 0},
		{0, 0, -1},
	},
	{
		{0, 0, 1},
		{-1, 0, 0},
		{0, -1, 0},
	},
	// +x -> +z 固定, +z 周りに 90°ずつ回転
	{
		{0, 1, 0},
		{0, 0, 1},
		{1, 0, 0},
	},
	{
		{0, 0, -1},
		{0, 1, 0},
		{1, 0, 0},
	},
	{
		{0, -1, 0},
		{0, 0, -1},
		{1, 0, 0},
	},
	{
		{0, 0, 1},
		{0, -1, 0},
		{1, 0, 0},
	},
	// +x -> -z 固定, -z 周りに 90°ずつ回転
	{
		{0, 0, 1},
		{0, 1, 0},
		{-1, 0, 0},
	},
	{
		{0, 1, 0},
		{0, 0, -1},
		{-1, 0, 0},
	},
	{
		{0, 0, -1},
		{0, -1, 0},
		{-1, 0, 0},
	},
	{
		{0, -1, 0},
		{0, 0, 1},
		{-1, 0, 0},
	},
};

class Vec3 {
   public:
	double x{0.0}, y{0.0}, z{0.0};

	Vec3 operator+(const Vec3& t) const {
		return Vec3{this->x + t.x, this->y + t.y, this->z + t.z};
	}

	Vec3 operator-(const Vec3& t) const {
		return Vec3{this->x - t.x, this->y - t.y, this->z - t.z};
	}

	void operator+=(const Vec3& t) {
		this->x += t.x;
		this->y += t.y;
		this->z += t.z;
	}

	bool operator!=(const Vec3& t) const {
		return (this->x != t.x or this->y != t.y or this->z != t.z);
	}

	bool operator<(const Vec3& t) const {
		if (this->x != t.x) return this->x < t.x;
		else if (this->y != t.y) return this->y < t.y;
		else return this->z < t.z;
	}
};

set<Vec3> ParseBars(const int n) {
	set<Vec3> bars;
	map<string, Vec3> labels;
	Vec3 current{0.0, 0.0, 0.0};

	for (int i = 0; i < n; i++) {
		string e;
		cin >> e;

		if (e == "+x") {
			bars.insert(current + Vec3{0.5, 0.0, 0.0});
			current += Vec3{1.0, 0.0, 0.0};
		} else if (e == "-x") {
			bars.insert(current + Vec3{-0.5, 0.0, 0.0});
			current += Vec3{-1.0, 0.0, 0.0};
		} else if (e == "+y") {
			bars.insert(current + Vec3{0.0, 0.5, 0.0});
			current += Vec3{0.0, 1.0, 0.0};
		} else if (e == "-y") {
			bars.insert(current + Vec3{0.0, -0.5, 0.0});
			current += Vec3{0.0, -1.0, 0.0};
		} else if (e == "+z") {
			bars.insert(current + Vec3{0.0, 0.0, 0.5});
			current += Vec3{0.0, 0.0, 1.0};
		} else if (e == "-z") {
			bars.insert(current + Vec3{0.0, 0.0, -0.5});
			current += Vec3{0.0, 0.0, -1.0};
		} else if (labels.find(e) == labels.end()) {
			labels.insert({e, current});
		} else {
			current = labels[e];
		}
	}

	return bars;
}

set<Vec3> RotateBars(const set<Vec3>& bars, const int i) {
	set<Vec3> rotated_bars;

	for (const Vec3& bar : bars) {
		Vec3 rotated_bar;
		rotated_bar.x = R[i][0][0] * bar.x + R[i][0][1] * bar.y + R[i][0][2] * bar.z;
		rotated_bar.y = R[i][1][0] * bar.x + R[i][1][1] * bar.y + R[i][1][2] * bar.z;
		rotated_bar.z = R[i][2][0] * bar.x + R[i][2][1] * bar.y + R[i][2][2] * bar.z;
		rotated_bars.insert(rotated_bar);
	}

	return rotated_bars;
}

bool IsSame(const set<Vec3>& bars1, const set<Vec3>& bars2) {
	if (bars1.size() != bars2.size()) return false;

	for (int i = 0; i < 24; i++) {
		set<Vec3> rotated_bars2;
		if (i == 0) rotated_bars2 = bars2;
		else rotated_bars2 = RotateBars(bars2, i);

		bool is_same = true;
		auto itr1 = bars1.begin(), itr2 = rotated_bars2.begin();
		const Vec3 difference = *itr1 - *itr2;
		for (itr1++, itr2++; itr1 != bars1.end(); itr1++, itr2++) {
			if (*itr1 - *itr2 != difference) {
				is_same = false;
				break;
			}
		}

		if (is_same) return true;
	}

	return false;
}

int main() {
	int n1, n2;
	set<Vec3> bars1, bars2;

	while (true) {
		cin >> n1;
		if (n1 == 0) break;
		bars1 = ParseBars(n1);
		cin >> n2;
		bars2 = ParseBars(n2);

		if (IsSame(bars1, bars2)) cout << "SAME" << endl;
		else cout << "DIFFERENT" << endl;
	}

	return 0;
}
