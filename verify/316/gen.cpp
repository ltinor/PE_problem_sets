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

    int D, K;
    if (mode == "small") {
        D = rand_ll(1, 5);
        K = rand_ll(1, min(D, 3));
    } else {
        D = rand_ll(6, 12);
        K = rand_ll(1, min(D/2, 6));
    }

    cout << D << " " << K << "\n";
    return 0;
}
