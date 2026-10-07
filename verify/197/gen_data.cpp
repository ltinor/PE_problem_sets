#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> tests(10);
    // Case 1: PE original N=10^12
    tests[0] = 1000000000000LL;
    // Case 2: Small N
    tests[1] = 0;
    tests[2] = 1;
    tests[3] = 10;
    tests[4] = 100;
    // Cases 5-7: Medium
    tests[5] = 1000;
    tests[6] = 1000000;
    tests[7] = 1000000000;
    // Cases 8-9: Random large
    tests[8] = rand_ll(1000000, 1000000000000LL);
    tests[9] = 500000000000LL;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << tests[i] << "\n";
    }

    return 0;
}
