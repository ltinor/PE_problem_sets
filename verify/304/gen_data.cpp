#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<tuple<ll,ll,ll>> cases(10);
    ll MOD = 1234567891011LL;

    // 1-3: small N, small starting prime
    cases[0] = {10, MOD, 100};
    cases[1] = {50, MOD, 1000};
    cases[2] = {100, MOD, 10000};

    // 4-6: medium
    cases[3] = {200, MOD, 100000};
    cases[4] = {500, MOD, 1000000};
    cases[5] = {1000, MOD, 10000000};

    // 7-8: larger (should be <1s)
    cases[6] = {2000, MOD, 100000000000000LL};
    cases[7] = {5000, MOD, 100000000000000LL};

    // 9-10: near limit
    cases[8] = {10000, MOD, 100000000000000LL};
    cases[9] = {20000, MOD, 100000000000000LL};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << get<0>(cases[i]) << " " << get<1>(cases[i]) << " " << get<2>(cases[i]) << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << get<0>(cases[i]) << "\n";
    }

    return 0;
}
