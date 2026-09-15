#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = argc > 1 ? argv[1] : "small";
    ll N = (mode == "small") ? rand_ll(1, 1000) : rand_ll(1e6, 1e9);
    cout << N << "\n";
    return 0;
}
