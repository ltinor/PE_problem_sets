#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Test cases: N S K T
    struct TC { int N, S, K, T; };
    vector<TC> cases(10);

    // 1: PE sample: 5 dice, 6-sided, top 3 sum to 15 → 1111 ways
    cases[0] = {5, 6, 3, 15};

    // 2: PE problem: 20 dice, 12-sided, top 10 sum to 70
    cases[1] = {20, 12, 10, 70};

    // 3-4: tiny
    cases[2] = {2, 3, 1, 1};
    cases[3] = {3, 4, 2, 5};

    // 5-6: small
    cases[4] = {4, 4, 2, 6};
    cases[5] = {3, 6, 2, 10};

    // 7-8: medium
    cases[6] = {6, 8, 3, 18};
    cases[7] = {8, 10, 4, 30};

    // 9-10: larger
    cases[8] = {10, 12, 5, 45};
    cases[9] = {15, 12, 8, 60};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fname);
        f << cases[i].N << " " << cases[i].S << " " << cases[i].K << " " << cases[i].T << "\n";
        f.close();
        cout << "Generated " << fname << "\n";
    }
    return 0;
}
