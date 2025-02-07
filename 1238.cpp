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

class Mat {
   private:
	vector<vector<int>> entries;

   public:
	int rows, cols;

	Mat(const int rows, const int cols)
		: rows(rows), cols(cols) {
		this->entries.resize(rows, vector<int>(cols));
	}

	void Resize(const int new_rows, const int new_cols) {
		if (this->rows != new_rows) {
			this->entries.resize(new_rows, vector<int>(this->cols));
			this->rows = new_rows;
		}
		if (this->cols != new_cols) {
			for (vector<int>& row : this->entries) row.resize(new_cols);
			this->cols = new_cols;
		}
	}

	vector<int>& operator[](size_t n) {
		return this->entries[n];
	}
};

bool Pivot(Mat& acm, const int k) {
	if (acm[k][k]) return true;
	for (int i = k + 1; i < acm.rows; i++) {
		if (acm[i][k] == 0) continue;
		swap(acm[k], acm[i]);
		return true;
	}
	return false;
}

bool SolveEquationSystem(Mat& acm, vector<int>& x) {
	if (acm.rows < acm.cols - 1) acm.Resize(acm.cols - 1, acm.cols);

	vector<int> s(acm.cols - 1);
	iota(s.begin(), s.end(), 0);

	// 前進消去
	for (int k = 0; k < acm.cols - 1; k++) {
		if (!Pivot(acm, k)) continue;
		for (int i = k + 1; i < acm.rows; i++) {
			if (acm[i][k] == 0) continue;
			int g = gcd(acm[k][k], acm[i][k]);
			int l = acm[k][k] / g, m = acm[i][k] / g;
			for (int j = k; j < acm.cols; j++) acm[i][j] = m * acm[k][j] - l * acm[i][j];
		}
	}

	// 後退代入
	x.resize(acm.cols - 1);
	for (int k = acm.cols - 2; k >= 0; k--) {
		x[k] = acm[k][acm.cols - 1];
		for (int j = k + 1; j < acm.cols - 1; j++) x[k] -= acm[k][j] * x[j];
		x[k] /= acm[k][k];
	}

	return true;
}

void Solve(Mat& acm) {
	vector<int> x;
	if (SolveEquationSystem(acm, x)) {
		for (int i = 0; i < x.size(); i++) {
			if (x[i] == 1) cout << (i + 1) << endl;
		}
		cout << "end" << endl;
	} else {
		cout << "no" << endl;
	}
}

int main(void) {
	while (true) {
		int n, p1, p2, p;
		cin >> n >> p1 >> p2;
		if (n == 0 and p1 == 0 and p2 == 0) break;
		p = p1 + p2;
		set<set<int>> appeared;
		Mat acm(n + 1, p + 1);
		for (int j = 0; j < p; j++) acm[0][j] = 1;
		acm[0][p] = p1 - p2;
		for (int i = 1; i <= n; i++) {
			int x, y;
			string a;
			cin >> x >> y >> a;
			x--;
			y--;
			if (x == y or appeared.find({x, y}) != appeared.end()) {
				i--;
				n--;
				continue;
			}
			appeared.insert({x, y});
			acm[i][x] = 1;
			acm[i][y] = (a == "yes" ? -1 : 1);
		}
		acm.Resize(n + 1, p + 1);
		Solve(acm);
	}
	return 0;
}
