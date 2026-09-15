#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc = {10, 50, 100, 200, 500, 1000, 2000, 10, 30, 800};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i + 1);
        ofstream f(fn);
        f << tc[i] << "\n";
    }
}
