#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases(10);

    // 1: PE sample T(10) = 2329
    cases[0] = 10;

    // 2-3: tiny (brute verifiable)
    cases[1] = 1;
    cases[2] = 2;

    // 4-5: small
    cases[3] = 3;
    cases[4] = 4;

    // 6-7: medium
    cases[5] = 5;
    cases[6] = 15;

    // 8-9: large
    cases[7] = 1000000;
    cases[8] = 1000000000000LL; // 10^12

    // 10: random large
    cases[9] = 987654321LL;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fname);
        f << cases[i] << "\n";
        f.close();
        cout << "Generated " << fname << " n=" << cases[i] << "\n";
    }
    return 0;
}
