#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> tests(10);

    // 1: PE original (n=10^10) -> answer: 268457129
    tests[0] = 10000000000LL;

    // 2-3: smallest
    tests[1] = 1;
    tests[2] = 2;

    // 4: n=5 (known: 293)
    tests[3] = 5;

    // 5: n=10 (known: 86195)
    tests[4] = 10;

    // 6: n=20 (known: 5227991891 mod 10^9)
    tests[5] = 20;

    // 7-8: small
    tests[6] = 3;
    tests[7] = 4;

    // 9-10: medium
    tests[8] = 6;
    tests[9] = 7;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << tests[i] << "\n";
    }

    return 0;
}
