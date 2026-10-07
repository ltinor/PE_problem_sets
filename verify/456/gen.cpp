#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll n;

    if (mode == "small") {
        // Small: verify against known examples: 8, 600, or random up to 1000
        ll choice = rand_ll(0, 3);
        if (choice == 0) n = 8;
        else if (choice == 1) n = 600;
        else n = rand_ll(3, 1000);
    } else if (mode == "large") {
        n = rand_ll(40000, 2000000);
    } else {
        n = 2000000;
    }

    cout << n << "\n";
    return 0;
}
