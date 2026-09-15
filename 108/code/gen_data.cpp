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

    // 1: sample K=2 → n=4 (n=4 has 3 solutions > 2)
    test_cases[0] = 2;

    // 2: K=5 → answer=6
    test_cases[1] = 5;

    // 3-4: small K
    test_cases[2] = 10;
    test_cases[3] = 20;

    // 5-6: medium
    test_cases[4] = 50;
    test_cases[5] = 100;

    // 7-8: larger
    test_cases[6] = 200;
    test_cases[7] = 500;

    // 9: random
    test_cases[8] = rand_ll(1, 800);

    // 10: original PE (K=1000) → 180180
    test_cases[9] = 1000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
