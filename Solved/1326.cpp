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

int main(void) {
	while (true) {
		int p, q;
		cin >> p >> q;
		if (q == 0) break;

		// P の解析
		vector<array<int, 4>> P;
		for (int i = 0, r = 0, c = 0, s = 0; i < p; i++) {
			string line;
			cin >> line;

			int indentation = 0;
			auto ch = line.begin();
			for (; *ch == '.'; ch++, indentation++);
			P.push_back({r, c, s, indentation});

			for (; ch != line.end(); ch++) {
				if (*ch == '(') r++;
				else if (*ch == ')') r--;
				else if (*ch == '{') c++;
				else if (*ch == '}') c--;
				else if (*ch == '[') s++;
				else if (*ch == ']') s--;
			}
		}

		// P に適合するスタイルを調べる
		vector<array<int, 3>> suitable_styles;
		for (int R = 1; R <= 20; R++) {
			for (int C = 1; C <= 20; C++) {
				for (int S = 1; S <= 20; S++) {
					bool is_suitable = true;
					for (const array<int, 4>& line : P) {
						if (R * line[0] + C * line[1] + S * line[2] != line[3]) {
							is_suitable = false;
							break;
						}
					}
					if (is_suitable) suitable_styles.push_back({R, C, S});
				}
			}
		}

		// Q に P のスタイルを適用した時のインデントを求める
		for (int i = 0, r = 0, c = 0, s = 0; i < q; i++) {
			string line;
			cin >> line;

			int indentation = suitable_styles[0][0] * r + suitable_styles[0][1] * c + suitable_styles[0][2] * s;
			for (int j = 1; j < suitable_styles.size(); j++) {
				if (suitable_styles[j][0] * r + suitable_styles[j][1] * c + suitable_styles[j][2] * s != indentation) {
					indentation = -1;
					break;
				}
			}

			cout << indentation << " \n"[i == q - 1];

			for (const char& ch : line) {
				if (ch == '(') r++;
				else if (ch == ')') r--;
				else if (ch == '{') c++;
				else if (ch == '}') c--;
				else if (ch == '[') s++;
				else if (ch == ']') s--;
			}
		}
	}

	return 0;
}
