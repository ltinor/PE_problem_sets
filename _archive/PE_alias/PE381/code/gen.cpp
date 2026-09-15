#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand()*rand()%(r-l+1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll n;
    if (mode == "small") n = rand_ll(5, 1000);
    else if (mode == "large") n = rand_ll(100000, 100000000);
    else n = atoll(argv[1]);

    cout << n << "\n";
}
