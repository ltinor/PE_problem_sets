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

    // 1: sample from problem — check for M=784 (p+q+r=784 is the example)
    test_cases[0] = 1000;

    // 2-4: small range
    for (int i = 1; i < 4; i++)
        test_cases[i] = rand_ll(100, 5000);

    // 5-7: medium range
    for (int i = 4; i < 7; i++)
        test_cases[i] = rand_ll(5000, 50000);

    // 8: max M
    test_cases[7] = 120000;

    // 9-10: random
    for (int i = 8; i < 10; i++)
        test_cases[i] = rand_ll(1000, 120000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
