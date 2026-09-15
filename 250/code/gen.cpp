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

    ll N, M;

    if (mode == "small") {
        N = rand_ll(1, 12);
        M = rand_ll(2, 10);
    } else if (mode == "large") {
        N = rand_ll(10, 100);
        M = rand_ll(10, 100);
    }

    cout << N << " " << M << "\n";
    return 0;
}
