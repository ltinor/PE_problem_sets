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

    ll n;
    if (mode == "small") {
        n = rand_ll(1, 100000);
    } else if (mode == "large") {
        n = rand_ll(1, 1LL << 30);
    } else {
        n = stoll(mode);
    }

    cout << n << "\n";
    return 0;
}
