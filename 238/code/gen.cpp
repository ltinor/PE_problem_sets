#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 238 gen

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll K;
    if (mode == "small") K = rand_ll(1, 100);
    else K = rand_ll(1000, 100000);

    cout << K << "\n";
    return 0;
}
