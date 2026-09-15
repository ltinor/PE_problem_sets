#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    vector<ll> test_cases(10);

    // 1: sample from problem: sum < 100000 = 124657
    test_cases[0] = 100000;

    // 2-3: small range
    for (int i = 1; i < 3; i++)
        test_cases[i] = rand_ll(1000, 100000);

    // 4-5: medium range
    for (int i = 3; i < 5; i++)
        test_cases[i] = rand_ll(100000, 100000000);

    // 6-7: large range near bound
    for (int i = 5; i < 7; i++)
        test_cases[i] = rand_ll(100000000000LL, 1000000000000LL);

    // 8: max M
    test_cases[7] = 1000000000000LL;

    // 9-10: random
    for (int i = 8; i < 10; i++)
        test_cases[i] = rand_ll(1, 1000000000000LL);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
