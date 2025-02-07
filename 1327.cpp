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

vector<vector<ll>> operator*(const vector<vector<ll>>& left, const vector<vector<ll>>& right) {
	int ln = left.size(), lm = left[0].size(), rm = right[0].size();
	vector<vector<ll>> result(ln, vector<ll>(rm, 0ll));

	for (int i = 0; i < ln; i++) {
		for (int j = 0; j < rm; j++) {
			for (int k = 0; k < lm; k++) {
				result[i][j] += left[i][k] * right[k][j];
			}
		}
	}

	return result;
}

vector<vector<ll>> operator%(const vector<vector<ll>>& mat, int M) {
	vector<vector<ll>> result(mat.size(), vector<ll>(mat[0].size(), 0ll));

	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			result[i][j] = mat[i][j] % M;
		}
	}

	return result;
}

vector<vector<ll>> MatPow(const vector<vector<ll>>& mat, int T, int M) {
	if (T == 0) {
		vector<vector<ll>> id(mat.size(), vector<ll>(mat[0].size(), 0ll));
		for (int k = 0; k < id.size(); k++) id[k][k] = 1;
		return id;
	}

	vector<vector<ll>> mat_half = MatPow(mat, T / 2, M);

	if (T % 2 == 0) {
		return (mat_half * mat_half) % M;
	} else {
		return (mat_half * mat_half * mat) % M;
	}
}

int main(void) {
	while (true) {
		int N, M, A, B, C, T;
		cin >> N >> M >> A >> B >> C >> T;
		if (N == 0) break;
		vector<vector<ll>> S(N, vector<ll>(1, 0ll));
		for (int i = 0; i < N; i++) cin >> S[i][0];

		vector<vector<ll>> mat(N, vector<ll>(N, 0ll));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j + 1) mat[i][j] = A;
				else if (i == j) mat[i][j] = B;
				else if (i == j - 1) mat[i][j] = C;
			}
		}
		mat = MatPow(mat, T, M);

		S = (mat * S) % M;

		for (int i = 0; i < N; i++) cout << S[i][0] << " \n"[i == N - 1] << flush;
	}

	return 0;
}

/*
			   [ B C 0 .. 0 ]
			   | A B C .. 0 |
	S(t + 1) = | 0 A B .. 0 | * S(t)
			   | : : : :: : |
			   [ 0 0 0 .. B ]
*/
