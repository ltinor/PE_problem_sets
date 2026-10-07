#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll N, MOD, START;
    MOD = 1234567891011LL;

    if (mode == "small") {
        N = rand_ll(5, 50);
        START = rand_ll(100, 10000);
    } else if (mode == "large") {
        N = rand_ll(50, 200);
        START = rand_ll(10000, 100000);
    } else {
        N = stoll(mode);
        START = 100000000000000LL;
    }

    cout << N << " " << MOD << " " << START << "\n";
    return 0;
}
