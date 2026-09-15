#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<pair<ll,ll>> tc = {{6,100},{10,200},{30,300},{210,100},{510510,1000},{510510,1000000}};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
