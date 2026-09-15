// PE 326 - Test case generator
#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    ll N, M;
    if (mode == "small") {
        N = rand_ll(1, 5000);
        M = rand_ll(1, min(N, 1000LL));
    } else if (mode == "medium") {
        N = rand_ll(5001, 100000);
        M = rand_ll(2, 10000);
    } else {
        N = rand_ll(100001, 2000000);
        M = rand_ll(10, 100000);
    }
    cout << N << " " << M << "\n";
}
