#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    vector<pair<ll,ll>> tc = {{3,1},{5,2},{10,3},{20,5},{50,10}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << tc[i].second << "\n";
    }
}
