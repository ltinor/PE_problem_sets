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

    // 1: PE original (K=2011) -> answer: 709313889
    tests[0] = 2011;

    // 2-3: tiny
    tests[1] = 1;
    tests[2] = 3;

    // 4-6: small
    tests[3] = 10;
    tests[4] = 20;
    tests[5] = 50;

    // 7-8: medium
    tests[6] = 100;
    tests[7] = 200;

    // 9-10: large
    tests[8] = 500;
    tests[9] = 1000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << tests[i] << "\n";
    }

    return 0;
}
