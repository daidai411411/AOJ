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

class Vec2 {
   public:
	double x, y;
};

double CompDistance(const Vec2 p1, const Vec2 p2, const double d) {
	return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) <= d * d);
}

vector<Vec2> Centers(const Vec2 p1, const Vec2 p2) {
	vector<Vec2> centers;

	Vec2 v12{p2.x - p1.x, p2.y - p1.y};
	double m12 = sqrt(v12.x * v12.x + v12.y * v12.y);
	double m13 = sqrt(4 - m12 * m12);
	Vec2 v13{m13 / m12 * (-v12.y), m13 / m12 * v12.x};
	for (int i = 0; i < 2; i++) {
		Vec2 center{p1.x + (v12.x + v13.x) / 2.0, p1.y + (v12.y + v13.y) / 2.0};
		centers.push_back(center);
		if (v13.x == 0.0 and v13.y == 0.0) break;
		v13 = {-v13.x, -v13.y};
	}

	return centers;
}

void chmax(int& a, const int b) {
	if (a < b) a = b;
}

int main() {
	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;

		vector<Vec2> points(n);
		vector<Vec2> centers;
		for (int i = 0; i < n; i++) {
			cin >> points[i].x >> points[i].y;
			for (int j = 0; j < i; j++) {
				if (!CompDistance(points[i], points[j], 2.0)) continue;

				vector<Vec2> new_centers = Centers(points[i], points[j]);
				centers.insert(centers.begin(), new_centers.begin(), new_centers.end());
			}
		}

		int max = 1;
		for (const Vec2& center : centers) {
			int count = 0;
			for (const Vec2 point : points) {
				if (CompDistance(center, point, 1.0001)) count++;
			}
			chmax(max, count);
		}

		cout << max << endl;
	}

	return 0;
}
