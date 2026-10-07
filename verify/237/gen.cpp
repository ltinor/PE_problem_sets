#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 237 gen: random n

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll n;
    if (mode == "small") n = rand_ll(1, 5);
    else n = rand_ll(1, 100);

    cout << n << "\n";
    return 0;
}
