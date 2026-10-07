#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll K, T;

    if (mode == "small") {
        K = rand_ll(2, 20);
        T = rand_ll(1, 5);
    } else if (mode == "large") {
        K = rand_ll(20, 200);
        T = rand_ll(5, 20);
    }

    cout << K << " " << T << "\n";
    return 0;
}
