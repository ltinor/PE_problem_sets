#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: sample (k=2000 → g_2000 = g_0+g_1 = 2)
    test_cases[0] = 2000;

    // 2-3: small
    test_cases[1] = 2001;
    test_cases[2] = 5000;

    // 4-6: medium
    test_cases[3] = 100000;
    test_cases[4] = 1000000;
    test_cases[5] = 10000000;

    // 7-8: large
    test_cases[6] = 1000000000000000000LL; // 10^18
    test_cases[7] = 500000000000000000LL;

    // 9-10: random large
    test_cases[8] = rand_ll(1e17, 1e18);
    test_cases[9] = rand_ll(1e17, 1e18);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }
    return 0;
}
