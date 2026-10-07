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

    // 1: PE sample: K=1000, sum=4742
    cases[0] = 1000;

    // 2-4: tiny
    cases[1] = 10;
    cases[2] = 50;
    cases[3] = 100;

    // 5-7: small
    cases[4] = 500;
    cases[5] = 2000;
    cases[6] = 5000;

    // 8-9: medium (hardcoded for PE answer verification)
    cases[7] = 100000;
    cases[8] = 2000000000000000LL; // 2e15

    // 10: random
    cases[9] = 10000;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fname);
        f << cases[i] << "\n";
        f.close();
        cout << "Generated " << fname << " K=" << cases[i] << "\n";
    }
    return 0;
}
