#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases(10);

    // 1. sample (N=50, small enough to verify manually)
    cases[0] = 50;

    // 2-3. small
    cases[1] = 10;
    cases[2] = 100;

    // 4-5. medium
    cases[3] = 500;
    cases[4] = 2000;

    // 6-7. large
    cases[5] = 100000;
    cases[6] = 5000000;

    // 8. PE answer check
    cases[7] = 100000000;

    // 9-10. random
    cases[8] = rand_ll(1000, 50000);
    cases[9] = rand_ll(100000, 1000000);

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << cases[i] << "\n";
    }
    return 0;
}
