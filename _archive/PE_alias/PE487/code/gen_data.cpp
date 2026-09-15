#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    vector<pair<ll,ll>> tc = {{3,2},{5,3},{10,5},{20,10},{50,20}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i].first << " " << tc[i].second << "\n";
    }
}
