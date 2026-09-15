#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<pair<ll,ll>> tc(10);
    tc[0] = {1, 10};   // F(1,10) = 41
    tc[1] = {10, 100}; // F(10,100) = 12492
    tc[2] = {2, 5};
    for (int i = 3; i < 6; i++) tc[i] = {rand_ll(1, 3), rand_ll(5, 15)};
    tc[6] = {1, 5};
    tc[7] = {5, 50};
    for (int i = 8; i < 10; i++) tc[i] = {rand_ll(1, 5), rand_ll(3, 20)};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i].first << " " << tc[i].second << "\n";
    }
}
