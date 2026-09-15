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

    ll bound;
    if (mode == "small") {
        bound = rand_ll(10, 1000);
    } else {
        bound = 100000000;
    }

    cout << bound << "\n";
}
