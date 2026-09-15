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

    ll U, K;
    if (mode == "small") {
        U = rand_ll(10, 30);
        K = rand_ll(1, 5);
    } else {
        U = rand_ll(30, 100);
        K = rand_ll(5, 20);
    }

    cout << U << " " << K << "\n";
    return 0;
}
