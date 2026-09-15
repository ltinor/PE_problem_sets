#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data");
    vector<pair<ll,ll>> tc = {{2,2},{3,3},{3,7},{12,3},{4,8},{10,10},{30,20},{50,30},{100,50},{200,100}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
