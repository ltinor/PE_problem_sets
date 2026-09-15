#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll rand_ll(ll l, ll r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll N;
    if (mode == "small") {
        N = rand_ll(100, 100000);
    } else if (mode == "large") {
        N = rand_ll(1000000, 100000000);
    } else {
        N = rand_ll(100, 100000000);
    }

    cout << N << "\n";
    return 0;
}
