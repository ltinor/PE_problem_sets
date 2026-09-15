#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: sample (N=25 → 49)
    test_cases[0] = 25;

    // 2: sample (N=120 → 159)
    test_cases[1] = 120;

    // 3-4: small
    test_cases[2] = 10;
    test_cases[3] = 1000;

    // 5-6: medium
    test_cases[4] = 100000;
    test_cases[5] = 10000000;

    // 7-8: random
    test_cases[6] = rand_ll(50000000, 500000000);
    test_cases[7] = rand_ll(1000000000, 5000000000LL);

    // 9: boundary - large
    test_cases[8] = 5000000000LL;

    // 10: original PE problem (N=10^10)
    test_cases[9] = 10000000000LL;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
