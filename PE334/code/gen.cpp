#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) { return l + (ll)rand() * rand() % (r - l + 1); }

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll t0 = rand_ll(1, 1000000), C = rand_ll(1, 1000000);
    int k = rand_ll(5, 15), M = rand_ll(2, 10);
    if (mode == "large") M = rand_ll(20, 100);
    else if (argc > 1) {
        // Custom: t0 C k M
    }
    cout << t0 << " " << C << " " << k << " " << M << "\n";
}
