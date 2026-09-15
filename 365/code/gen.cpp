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

    ll N, K, L, R;
    if (mode == "small") {
        N = rand_ll(10, 100);
        K = rand_ll(1, N/2);
        L = 3;
        R = 15;
    } else if (mode == "large") {
        N = rand_ll(1000000, 10000000);
        K = rand_ll(1000, 10000);
        L = 100;
        R = 200;
    } else { // custom
        // Default to PE problem
        N = 1000000000000000000LL;
        K = 1000000000;
        L = 1000;
        R = 5000;
    }

    cout << N << " " << K << " " << L << " " << R << "\n";
    return 0;
}
