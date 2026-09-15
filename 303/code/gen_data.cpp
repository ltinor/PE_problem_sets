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

    // 1-2: small samples
    cases[0] = 10;
    cases[1] = 42;

    // 3-4: medium
    cases[2] = 100;
    cases[3] = 200;

    // 5-7: larger
    cases[4] = 500;
    cases[5] = 1000;
    cases[6] = 2000;

    // 8-10: near max
    cases[7] = 5000;
    cases[8] = 8000;
    cases[9] = 10000;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << cases[i] << "\n";
    }

    return 0;
}
