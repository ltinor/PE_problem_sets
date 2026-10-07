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

    ll r1, r2;
    if (mode == "small") {
        // Small rows where brute can verify
        r1 = rand_ll(2, 15);
        r2 = rand_ll(2, 15);
    } else if (mode == "pe") {
        r1 = 5678027;
        r2 = 7208785;
    } else {
        r1 = rand_ll(2, 100);
        r2 = rand_ll(2, 100);
    }

    cout << r1 << " " << r2 << "\n";
}
