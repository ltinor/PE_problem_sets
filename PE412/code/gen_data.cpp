#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<pair<ll,ll>> tc = {{3,0},{5,3},{6,3},{2,1},{4,2},{3,1},{2,0},{4,0},{3,2},{10,5}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
