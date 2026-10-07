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

    ll limit;
    if (mode == "small") {
        limit = rand_ll(10, 1000);
    } else if (mode == "large") {
        limit = rand_ll(100000, 1000000);
    } else {
        limit = stoll(mode);
    }

    cout << limit << "\n";
    return 0;
}
