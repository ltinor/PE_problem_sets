#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll m, n;
    if (mode == "small") { m = rand_ll(1, 4); n = rand_ll(1, 4); }
    else if (mode == "large") { m = rand_ll(5, 12); n = rand_ll(5, 12); }
    else { m = atoll(argv[1]); n = atoll(argv[2]); }
    cout << m << " " << n << "\n";
}
