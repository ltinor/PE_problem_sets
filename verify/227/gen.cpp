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
    if (mode == "small") {
        // small even numbers (avoid N=2 for Monte Carlo variance)
        vector<int> small = {4, 6, 8, 10, 12};
        N = small[rand() % small.size()];
    } else if (mode == "large") {
        // larger even numbers
        N = 2 * (int)rand_ll(10, 500);
    }

    cout << N << "\n";
    return 0;
}
