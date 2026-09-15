#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<pair<ll,ll>> tc(10);
    tc[0] = {3, 2};    // E(3,2) = 2
    tc[1] = {8, 3};    // E(8,3) = 16/7 ≈ 2.28571
    tc[2] = {10, 2};   // one cut: E = 10/4 = 2.5
    for (int i = 3; i < 6; i++) tc[i] = {rand_ll(5, 15), rand_ll(2, 5)};
    tc[6] = {5, 2};    // E = 1.25
    tc[7] = {20, 5};
    for (int i = 8; i < 10; i++) tc[i] = {rand_ll(10, 30), rand_ll(2, 6)};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
