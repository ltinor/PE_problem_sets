#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 240 gen

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, S, K, T;
    if (mode == "small") {
        N = rand_ll(2, 5);
        S = rand_ll(2, 6);
        K = rand_ll(1, N);
        T = rand_ll(K, K * S);
    } else {
        N = rand_ll(5, 10);
        S = rand_ll(2, 12);
        K = rand_ll(1, N);
        T = rand_ll(K, K * S);
    }
    cout << N << " " << S << " " << K << " " << T << "\n";
    return 0;
}
