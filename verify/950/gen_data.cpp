#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

// Generate reduced test data for PE 950 (simple version).
// Input format: N C m  (n pirates, C coins, p = 1/sqrt(m)).
// Reduced ranges keep the simulation (O(N*C)) comfortably fast.

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    // 10 cases: (N, C, m)
    // validation points first (they are the known PE checkpoints)
    vector<array<long long,3>> cases = {
        {30,    3,    3},   // T = 190
        {50,    3,   31},   // T = 385
        {1000, 101, 101},   // T = 142427
    };

    // a few random small / medium cases
    for (int i = 0; i < 3; ++i) {
        cases.push_back({rand_ll(1, 60),      rand_ll(1, 30),   rand_ll(2, 300)});
    }
    for (int i = 0; i < 2; ++i) {
        cases.push_back({rand_ll(1, 2000),    rand_ll(1, 200),  rand_ll(2, 5000)});
    }
    // large cases near the reduced upper bound
    cases.push_back({100000, 1000, 999983});   // large N, C, prime m
    cases.push_back({1, 1, 2});                // minimum

    // ensure m is never a perfect square (keeps p irrational)
    for (auto &c : cases) {
        long long r = (long long)sqrtl((long double)c[2]);
        if (r * r == c[2]) c[2]++;  // bump to a non-square
    }

    for (size_t i = 0; i < cases.size(); ++i) {
        char name[64];
        snprintf(name, sizeof(name), "data/%02zu.in", i + 1);
        ofstream fout(name);
        fout << cases[i][0] << " " << cases[i][1] << " " << cases[i][2] << "\n";
        fout.close();
        cout << "Generated " << name << " : N=" << cases[i][0]
             << " C=" << cases[i][1] << " m=" << cases[i][2] << "\n";
    }

    return 0;
}
