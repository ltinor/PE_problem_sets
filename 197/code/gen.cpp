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

    ll N;
    if (mode == "small") {
        N = rand_ll(0, 200);
    } else if (mode == "large") {
        N = rand_ll(1000, 1000000000000LL);
    } else {
        N = rand_ll(0, 1000000);
    }

    cout << N << "\n";
}
