#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    // Format: k N (test cases as pairs)
    // For OJ, use single test case format: "k N"
    // 10 test cases with small values
    vector<pair<int,ll>> tc = {
        {1, 10}, {1, 100}, {2, 10}, {2, 50}, {3, 20},
        {3, 100}, {4, 10}, {5, 20}, {1, 5}, {2, 30}
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << tc[i].second << "\n";
    }
}
