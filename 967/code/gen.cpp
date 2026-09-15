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

    ll N;
    int B;

    if (mode == "small") {
        N = rand_ll(1, 1000000);
        B = rand() % 40 + 1;   // 1..40
    } else if (mode == "large") {
        N = rand_ll(1, 1000000000000000000LL);
        B = rand() % 40 + 1;
    }

    assert(N >= 1 && N <= 1000000000000000000LL);
    assert(B >= 1 && B <= 40);

    cout << N << " " << B << "\n";
}
