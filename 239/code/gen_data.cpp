#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases: (N, K)
    vector<pair<int,int>> cases(10);

    // 1: PE case
    cases[0] = {100, 22};

    // 2-3: tiny
    cases[1] = {3, 1};
    cases[2] = {5, 2};

    // 4-5: small
    cases[3] = {8, 3};
    cases[4] = {10, 2};

    // 6-7: medium
    cases[5] = {20, 5};
    cases[6] = {50, 10};

    // 8-9: large
    cases[7] = {100, 10};
    cases[8] = {200, 20};

    // 10: boundary
    cases[9] = {100, 25}; // all primes displaced

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fname);
        f << cases[i].first << " " << cases[i].second << "\n";
        f.close();
        cout << "Generated " << fname << " N=" << cases[i].first << " K=" << cases[i].second << "\n";
    }
    return 0;
}
