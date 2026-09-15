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

    int N;
    ll T;
    if (mode == "small") {
        N = rand() % 30 + 1;
        T = rand_ll(1, 1000000);
    } else {
        N = rand() % 100 + 1;
        T = rand_ll(1, 1000000000000LL);
    }

    assert(N >= 1 && N <= 100);
    assert(T >= 1 && T <= 1000000000000LL);

    cout << "1\n" << N << " " << T << "\n";
    return 0;
}
