#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases(10);

    // 1-2: small samples for verification
    cases[0] = 10;
    cases[1] = 100;

    // 3-5: medium
    for (int i = 2; i < 5; i++) {
        cases[i] = rand_ll(1000, 1000000);
    }

    // 6-8: large
    for (int i = 5; i < 8; i++) {
        cases[i] = rand_ll(10000000, 1LL << 30);
    }

    // 9: boundary
    cases[8] = 1LL << 30; // 2^30

    // 10: random
    cases[9] = rand_ll(1, 1LL << 30);

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " n=" << cases[i] << "\n";
    }

    return 0;
}
