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

    ll A, B, C;

    if (mode == "small") {
        A = rand_ll(1, 1000);
        B = rand_ll(1, 1000);
        C = rand_ll(0, 1000);
    } else if (mode == "large") {
        A = rand_ll(1, 100000);
        B = rand_ll(1, 10000000);
        C = rand_ll(0, 100000);
    }

    assert(B >= 1 && B <= 10000000);
    assert(A >= 1 && A <= 100000);
    assert(C >= 0 && C <= 100000);

    cout << A << " " << B << " " << C << "\n";
    return 0;
}
