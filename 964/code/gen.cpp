#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand((unsigned)time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll k;
    if (mode == "small") {
        k = rand_ll(1, 4);          // brute-forceable (T <= 7)
    } else {
        k = rand_ll(5, 7);          // larger, only std handles
    }
    assert(k >= 1 && k <= 7);
    cout << k << "\n";
    return 0;
}
