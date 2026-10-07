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

    ll K;
    if (mode == "small") {
        K = rand_ll(1, 5);
    } else if (mode == "large") {
        K = rand_ll(6, 13);
    } else {
        K = stoll(mode);
    }

    cout << K << "\n";
    return 0;
}
