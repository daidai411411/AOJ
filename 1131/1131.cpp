#include <algorithm>
#include <array>
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

void ReduceFraction(int& p, int& q) {
    int g = gcd(p, q);
    p /= g;
    q /= g;
}

void Solve(int p, int q, int a, int n) {
    ReduceFraction(p, q);
    cout << p << '/' << q << endl;
    return;
}

int main(void) {
    int p, q, a, n;
    while (true) {
        cin >> p >> q >> a >> n;
        if (p == 0) break;
        Solve(p, q, a, n);
    }
    return 0;
}

/*

1/2 = 1/7 + 1/7 + 1/7 + 1/14 (積=4802)

1/3 = 1/7 + 1/7 + 1/21 (積=1029)

2/3 = 1/5 + 1/5 + 1/5 + 1/15 (積=1875)

1/6 = 1/10 + 1/15

*/
