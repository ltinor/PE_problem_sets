#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll n, m;
    if (mode == "small") { n = rand_ll(5, 20); m = rand_ll(2, min(n, 5LL)); }
    else if (mode == "large") { n = rand_ll(100, 1000); m = rand_ll(2, 12LL); }
    else { n = rand_ll(10, 30); m = rand_ll(2, 6); }
    cout << n << " " << m << "\n";
}
