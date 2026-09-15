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

    // 1: sample (PE original: T = 10^12)
    test_cases[0] = 1000000000000LL;

    // 2-3: small
    test_cases[1] = 1;
    test_cases[2] = 10;

    // 4-6: medium
    test_cases[3] = 100;
    test_cases[4] = 1000;
    test_cases[5] = 1000000;

    // 7-8: large random
    test_cases[6] = rand_ll(1000000000LL, 100000000000LL);
    test_cases[7] = rand_ll(100000000000LL, 1000000000000LL);

    // 9-10: more random
    test_cases[8] = rand_ll(10000, 10000000);
    test_cases[9] = 500000000000LL;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with T = " << test_cases[i] << "\n";
    }

    return 0;
}
