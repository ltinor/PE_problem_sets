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
    ll A, B;
    if (mode == "small") {
        A = rand_ll(1, 100);
        B = A + rand_ll(1, 100);
    } else {
        A = rand_ll(1, 100000);
        B = A + rand_ll(1, 100000);
    }
    cout << A << " " << B << "\n";
    return 0;
}
