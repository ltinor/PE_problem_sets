#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data");
    vector<pair<ll,ll>> tc = {{5,3},{10,10},{20,5},{50,10},{100,20},{200,30},{500,50},{1000,100},{10000,50},{100000,100}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
