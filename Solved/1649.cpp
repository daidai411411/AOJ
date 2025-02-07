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

bool Pivot(int k, vector<vector<int>>& mat, int p) {
    if (mat[p][p] != 0) return true;
    for (int r = p + 1; r < k; r++) {
        if (mat[r][p] == 0) continue;
        swap(mat[p], mat[r]);
        return true;
    }
    return false;
}

bool IsFullRank(int k, vector<vector<int>>& mat) {
    for (int p = 0; p < k; p++) {
        if (!Pivot(k, mat, p)) return false;
        for (int r = p + 1; r < k; r++) {
            if (mat[r][p] == 0) continue;
            int l = lcm(mat[p][p], mat[r][p]);
            int a = l / mat[p][p];
            int b = l / mat[r][p];
            for (int c = p; c < k + 1; c++) {
                mat[r][c] = a * mat[p][c] - b * mat[r][c];
            }
        }
    }
    return true;
}

int main() {
    while (true) {
        int w, h;
        cin >> w >> h;
        if (w == 0) break;
        int k = w + h - 1;
        vector<vector<int>> mat(k, vector<int>(k + 1, 0));
        for (int i = 0; i < k; i++) {
            int x, y, n;
            cin >> x >> y >> n;
            x -= 2;
            y += w - 2;
            if (x == -1) {
                mat[i][y] = 1;
                mat[i][k] = n;
            } else {
                mat[i][x] = mat[i][y] = 1;
                mat[i][k] = n;
            }
        }

        if (IsFullRank(k, mat)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
