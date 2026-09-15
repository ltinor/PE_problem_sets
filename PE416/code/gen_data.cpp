#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    // Test cases: (m, n) pairs
    vector<pair<ll,ll>> tc = {{1,3},{1,4},{1,5},{2,3},{2,100},{10,1000000000000LL}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
