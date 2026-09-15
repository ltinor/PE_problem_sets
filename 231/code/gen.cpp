#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll N, K;
    if (mode == "small") {
        N = rand_ll(2, 25);
        K = rand_ll(1, N - 1);
    } else {
        N = rand_ll(100000, 5000000);
        K = rand_ll(1, N - 1);
    }

    cout << N << " " << K << "\n";
    return 0;
}
