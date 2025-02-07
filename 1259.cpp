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

/* 各回転における各面の行き先
	↓数字と面の対応
	0 +x
	1 +y
	2 +z
	3 -z
	4 -y
	5 -x
*/
const int R[24][6]{
	// +x -> +x 固定, +x 周りに 90°ずつ回転
	{0, 1, 2, 3, 4, 5},
	{0, 2, 4, 1, 3, 5},
	{0, 4, 3, 2, 1, 5},
	{0, 3, 1, 4, 2, 5},
	// +x -> -x 固定, -x 周りに 90°ずつ回転
	{5, 2, 1, 4, 3, 0},
	{5, 1, 3, 2, 4, 0},
	{5, 3, 4, 1, 2, 0},
	{5, 4, 2, 3, 1, 0},
	// +x -> +y 固定, +y 周りに 90°ずつ回転
	{1, 2, 0, 5, 3, 4},
	{1, 0, 3, 2, 5, 4},
	{1, 3, 5, 0, 2, 4},
	{1, 5, 2, 3, 0, 4},
	// +x -> -y 固定, -y 周りに 90°ずつ回転
	{4, 0, 2, 3, 5, 1},
	{4, 2, 5, 0, 3, 1},
	{4, 5, 3, 2, 0, 1},
	{4, 3, 0, 5, 2, 1},
	// +x -> +z 固定, +z 周りに 90°ずつ回転
	{2, 0, 1, 4, 5, 3},
	{2, 1, 5, 0, 4, 3},
	{2, 5, 4, 1, 0, 3},
	{2, 4, 0, 5, 1, 3},
	// +x -> -z 固定, -z 周りに 90°ずつ回転
	{3, 1, 0, 5, 4, 2},
	{3, 0, 4, 1, 5, 2},
	{3, 4, 5, 0, 1, 2},
	{3, 5, 1, 4, 0, 2},
};

vector<string> RotateCube(const vector<string>& cube, const int ri) {
	if (ri == 0) return cube;

	vector<string> rotated_cube(6);
	for (int j = 0; j < 6; j++) {
		rotated_cube[R[ri][j]] = cube[j];
	}
	return rotated_cube;
}

int CountFacesToBeRepainted(const vector<vector<string>>& cubes) {
	int count = 0;
	for (int f = 0; f < 6; f++) {
		map<string, int> numof_colors;
		int max_numof_color = 0;
		for (vector<string> cube : cubes) {
			numof_colors[cube[f]]++;
			max_numof_color = max(max_numof_color, numof_colors[cube[f]]);
		}

		count += cubes.size() - max_numof_color;
	}

	return count;
}

int main() {
	int n;

	while (true) {
		cin >> n;
		if (n == 0) break;
		vector<vector<string>> cubes(n, vector<string>(6));
		for (vector<string>& cube : cubes) {
			for (string& color : cube) {
				cin >> color;
			}
		}

		int ri[4]{0};
		int ri_max[4]{0};
		for (int i = 1; i < n; i++) ri_max[i] = 23;

		int minimum = 100;
		vector<vector<string>> rotated_cubes(n, vector<string>(6));
		rotated_cubes[0] = cubes[0];
		for (ri[1] = 0; ri[1] <= ri_max[1]; ri[1]++) {
			for (ri[2] = 0; ri[2] <= ri_max[2]; ri[2]++) {
				for (ri[3] = 0; ri[3] <= ri_max[3]; ri[3]++) {
					for (int i = 1; i < n; i++) {
						rotated_cubes[i] = RotateCube(cubes[i], ri[i]);
					}
					minimum = min(minimum, CountFacesToBeRepainted(rotated_cubes));
				}
			}
		}

		cout << minimum << endl;
	}

	return 0;
}
