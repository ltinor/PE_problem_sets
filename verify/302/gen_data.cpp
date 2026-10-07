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

    // 1-2: tiny samples
    cases[0] = 100;
    cases[1] = 10000; // PE says 7

    // 3-5: small
    cases[2] = 100000;
    cases[3] = 1000000;
    cases[4] = 5000000;

    // 6-8: medium (should be <1s)
    cases[5] = 100000000; // PE says 656
    cases[6] = 500000000;
    cases[7] = 1000000000;

    // 9-10: large (near 1s limit)
    cases[8] = 2000000000LL;
    cases[9] = 4000000000LL;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << cases[i] << "\n";
    }

    return 0;
}
