#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

string rand_seq(int len) {
    string s;
    for (int i = 0; i < len; i++) {
        int r = rand() % 3;
        s += "DUd"[r];
    }
    return s;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    string S;
    ll T;

    if (mode == "small") {
        S = rand_seq(rand() % 5 + 2);
        T = rand_ll(0, 100);
    } else if (mode == "large") {
        // Use the PE sequence
        S = "UDDDUdddDDUDDddDdDddDDUDDdUUDd";
        T = 1000000000000000LL;
    } else {
        S = mode;  // pass sequence directly
        T = 0;
    }

    cout << S << " " << T << "\n";
    return 0;
}
