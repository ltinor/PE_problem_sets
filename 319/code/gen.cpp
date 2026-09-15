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

    ll n;
    if (mode == "small") {
        n = rand_ll(1, 6);
    } else {
        n = rand_ll(7, 10);
    }

    cout << n << "\n";
    return 0;
}
