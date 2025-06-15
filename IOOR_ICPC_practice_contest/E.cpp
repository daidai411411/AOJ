#include <algorithm>
#include <array>
#include <climits>
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

template <typename T>
bool ChMax(T& max, T val) {
	return (val > max) ? (max = val, true) : false;
}

template <typename T>
bool ChMin(T& max, T val) {
	return (val < max) ? (max = val, true) : false;
}

template <typename T>
T TopPop(stack<T>& s) {
	T value = s.top();
	s.pop();
	return value;
}

pair<array<string, 3>, char> Parse(string expression) {
	vector<string> rpns(1, "");
	int depth = 0;
	char root, operator_char = -1;
	for (char c : expression) {
		if (isdigit(c)) {
			rpns.back() += c;
			if (operator_char != -1) {
				rpns.back() += operator_char;
				operator_char = -1;
			}
		} else if (c == '(') depth++;
		else if (c == ')') depth--;
		else if (depth == 0) {
			rpns.push_back("");
			root = c;
		} else operator_char = c;
	}
	return {{rpns[0], rpns[1], rpns[2]}, root};
}

int EvalRpn(string rpn) {
	stack<int> operands;
	for (int i = 0; i < rpn.length(); i++) {
		if (isdigit(rpn[i])) operands.push(rpn[i] - '0');
		else {
			int n2 = TopPop(operands);
			int n1 = TopPop(operands);
			if (rpn[i] == '+') operands.push(n1 + n2);
			else operands.push(n1 - n2);
		}
	}
	return operands.top();
}

string Concat(stack<string> s) {
	string result = "";
	while (!s.empty()) result = TopPop(s) + result;
	return result;
}

vector<string> Adjacents(const string current) {
	vector<string> adjacents;

	stack<string> children;
	for (int i = 0; i < current.length(); i++) {
		if (isdigit(current[i])) children.push({current[i]});
		else {
			string c2 = TopPop(children);
			string c1 = TopPop(children);
			if (current[i] == '-') adjacents.push_back(Concat(children) + c2 + c1 + current.substr(i));
			children.push(c1 + c2 + current[i]);
		}
	}

	return adjacents;
}

void Dfs(const string current, set<string>& seen, int& min_value, int& max_value, int d = 0) {
	// for (int i = 0; i < d; i++) cout << '|';
	// cout << current << " : " << EvalRpn(current);
	// cout << " -> ";
	// for (string adjacent : Adjacents(current)) cout << adjacent << ' ';
	// cout << endl;

	seen.insert(current);
	int value = EvalRpn(current);
	ChMin(min_value, value);
	ChMax(max_value, value);

	for (string adjacent : Adjacents(current)) {
		if (seen.find(adjacent) != seen.end()) continue;
		Dfs(adjacent, seen, min_value, max_value, d + 1);
	}
}

pair<int, int> CalcMinMax(string rpn) {
	set<string> seen;
	int min_value = INT_MAX, max_value = INT_MIN;
	Dfs(rpn, seen, min_value, max_value);
	return {min_value, max_value};
}

bool Solve(void) {
	string expression;
	cin >> expression;
	if (expression == "-1") return false;

	auto [rpns, root] = Parse(expression);
	array<int, 3> min_values, max_values;
	for (int i = 0; i < 3; i++) tie(min_values[i], max_values[i]) = CalcMinMax(rpns[i]);

	for (int i = 0; i < 3; i++) cout << rpns[i] << " : " << min_values[i] << " , " << max_values[i] << endl;
	cout << root << endl;

	cout << "" << endl;

	return true;
}

int main(void) {
	while (Solve());
	return 0;
}
