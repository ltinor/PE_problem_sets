#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand((unsigned)time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll M;

    if (mode == "small") {
        // Small enough for brute to handle quickly
        M = rand_ll(100, 3000);
    } else if (mode == "large") {
        M = rand_ll(3000, 120000);
    }

    assert(M >= 1 && M <= 120000);

    cout << M << "\n";
    return 0;
}
