#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    ll M;
    if (mode == "small") {
        N = rand_ll(1, 8);
        M = 1000000007;
    } else if (mode == "large") {
        N = rand_ll(100, 1000);
        M = 1000000007;
    } else {
        N = stoi(mode);
        M = 1000000007;
    }

    cout << N << " " << M << "\n";
    return 0;
}
