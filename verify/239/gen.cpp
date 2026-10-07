#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 239 gen

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, K;
    if (mode == "small") {
        N = rand_ll(1, 8);
        K = rand_ll(0, N);
    } else {
        N = rand_ll(10, 100);
        K = rand_ll(0, N / 4);
    }
    cout << N << " " << K << "\n";
    return 0;
}
