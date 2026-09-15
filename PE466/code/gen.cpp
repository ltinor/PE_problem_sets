#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll m, n;
    if (mode == "small") {
        m = rand_ll(2, 8);
        n = rand_ll(2, 20);
    } else if (mode == "large") {
        m = rand_ll(9, 25);
        n = rand_ll(100, 100000);
    } else if (mode == "PE") {
        m = 64; n = 10000000000000000LL;
    } else {
        m = atoll(argv[1]);
        n = atoll(argv[2]);
    }
    cout << m << " " << n << "\n";
}
