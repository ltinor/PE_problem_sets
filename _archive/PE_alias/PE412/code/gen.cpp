#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll m, n;
    if (mode == "small") { m = rand_ll(2, 5); n = rand_ll(0, m-1); }
    else if (mode == "large") { m = rand_ll(6, 50); n = rand_ll(0, m-1); }
    else { m = atoll(argv[1]); n = atoll(argv[2]); }
    cout << m << " " << n << "\n";
}
