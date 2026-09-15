#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    // Format: N D pairs
    vector<pair<ll,ll>> tc = {
        {84, 4}, {12, 12}, {50, 123}, {8, 5},
        {7, 3}, {6, 2}, {1000000, 65432}
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
