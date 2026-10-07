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
    if (mode == "small") {
        N = rand_ll(1, 3); // k=1,2,3 only (quick)
    } else if (mode == "large") {
        N = rand_ll(10, 15);
    } else {
        N = stoi(mode);
    }

    cout << N << "\n";
    return 0;
}
