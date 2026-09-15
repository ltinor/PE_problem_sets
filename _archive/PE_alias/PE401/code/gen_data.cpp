#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main() {
    system("mkdir -p data"); srand(time(0));
    ll M = 1'000'000'000;
    vector<ll> tc = {6, 10, 100, 1000, 1, 50, 500, 2000, 10000, (ll)100000};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i + 1);
        ofstream f(fn);
        f << tc[i] << " " << M << "\n";
    }
}
