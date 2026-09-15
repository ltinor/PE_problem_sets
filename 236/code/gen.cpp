#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 236 gen: random small test cases

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    vector<pair<ll,ll>> prods(5);

    if (mode == "small") {
        // Small random: a_i, b_i in [1, 10]
        for (int i = 0; i < 5; i++) {
            prods[i] = {rand_ll(1, 10), rand_ll(1, 10)};
        }
    } else {
        // PE data
        prods[0] = {5248, 640};
        prods[1] = {1312, 1888};
        prods[2] = {2624, 3776};
        prods[3] = {5760, 3776};
        prods[4] = {3936, 5664};
    }

    for (auto [x, y] : prods) cout << x << " " << y << "\n";
    return 0;
}
