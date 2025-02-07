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

	Vec2()
		: x(0), y(0) {};

	Vec2(const double& x, const double& y)
		: x(x), y(y) {};

	double Mag() const {
		return sqrt(this->x * this->x + this->y * this->y);
	}

	Vec2 operator+(const Vec2& t) const {
		return Vec2{this->x + t.x, this->y + t.y};
	}

	Vec2 operator-(const Vec2& t) const {
		return Vec2{this->x - t.x, this->y - t.y};
	}

	Vec2 operator/(const double& t) const {
		return Vec2{this->x / t, this->y / t};
	}

	friend Vec2 operator*(const double& t, const Vec2 vec2) {
		return Vec2{t * vec2.x, t * vec2.y};
	}

	bool operator==(const Vec2 t) const {
		return (this->x == t.x and this->y == t.y);
	}
};

class Circle {
   public:
	Vec2 center;
	double radius;

	Circle()
		: center(Vec2{0.0, 0.0}), radius(0.0) {};

	Circle(const Vec2& center, const double& radius)
		: center(center), radius(radius) {};
};

Circle Incircle(const array<Vec2, 3>& vertices) {
	Circle incircle;

	double m12 = (vertices[1] - vertices[2]).Mag();
	double m20 = (vertices[2] - vertices[0]).Mag();
	double m01 = (vertices[0] - vertices[1]).Mag();
	incircle.center = (m12 * vertices[0] + m20 * vertices[1] + m01 * vertices[2]) / (m12 + m20 + m01);
	double s = (m12 + m20 + m01) / 2.0;
	incircle.radius = sqrt(s * (s - m12) * (s - m20) * (s - m01)) / s;

	return incircle;
}

Circle AnotherCircle(const Vec2& vertice, const Circle& incircle, const Vec2& v_to_i, const Circle& circle0) {
	Circle circle;

	double l{0.0}, r{1.0};
	const double threshold{0.0000001};
	while (true) {
		double m = (l + r) / 2.0;

		circle = Circle{vertice + m * v_to_i, m * incircle.radius};

		if ((circle0.radius + circle.radius) > (circle0.center - circle.center).Mag()) r = m;
		else l = m;

		if ((r - l) * incircle.radius < threshold) break;
	}

	return circle;
}

bool solve() {
	array<Vec2, 3> vertices;
	for (Vec2& vertice : vertices) cin >> vertice.x >> vertice.y;
	if (vertices[0] == vertices[1]) return false;

	Circle incircle = Incircle(vertices);
	array<Vec2, 3> v_to_i{incircle.center - vertices[0], incircle.center - vertices[1], incircle.center - vertices[2]};
	array<Circle, 3> circles;

	double l{0.0}, r{1.0};
	const double threshold{0.0000001};
	while (true) {
		double m = (l + r) / 2.0;

		circles[0] = Circle{vertices[0] + m * v_to_i[0], m * incircle.radius};
		circles[1] = AnotherCircle(vertices[1], incircle, v_to_i[1], circles[0]);
		circles[2] = AnotherCircle(vertices[2], incircle, v_to_i[2], circles[0]);

		if ((circles[1].radius + circles[2].radius) > (circles[1].center - circles[2].center).Mag()) l = m;
		else r = m;

		if ((r - l) * incircle.radius < threshold) break;
	}

	cout << fixed << setprecision(6);
	cout << circles[0].radius << " " << circles[1].radius << " " << circles[2].radius << endl;

	return true;
}

int main() {
	while (solve());
	return 0;
}