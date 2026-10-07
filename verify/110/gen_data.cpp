#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: sample K=100 → n=1260
    test_cases[0] = 100;

    // 2-3: small
    test_cases[1] = 1;
    test_cases[2] = 5;

    // 4-5: medium
    test_cases[3] = 10;
    test_cases[4] = 50;

    // 6-7: larger
    test_cases[5] = 200;
    test_cases[6] = 500;

    // 8: K=1000 → same as PE 108 answer (180180)
    test_cases[7] = 1000;

    // 9: K=100000
    test_cases[8] = 100000;

    // 10: original PE (K=4000000 → 9350130049860600)
    test_cases[9] = 4000000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
