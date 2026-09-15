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
    if (mode == "small") n = 4;
    else if (mode == "medium") n = 10;
    else if (mode == "large") n = 100;
    else n = atoll(argv[1]);
    cout << n << "\n";
}
