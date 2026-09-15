#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data");
    vector<pair<ll,ll>> tc = {
        {3, 4}, {6, 10}, {10, 20}, {8, 100},
        {12, 345}, {64, 64}, {15, 1000},
        {20, 10000}, {25, 100000}, {64, 10000000000000000LL}
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << tc[i].second << "\n";
    }
}
