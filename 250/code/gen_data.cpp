#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<ll, ll>> test_cases(10);

    // 1: sample (PE original)
    test_cases[0] = {250250, 250};

    // 2-3: small N, small M
    test_cases[1] = {5, 3};
    test_cases[2] = {10, 5};

    // 4-5: medium N (for brute verification)
    test_cases[3] = {20, 5};
    test_cases[4] = {50, 10};

    // 6-7: larger N, smaller M
    test_cases[5] = {100, 7};
    test_cases[6] = {500, 3};

    // 8: edge - N=1
    test_cases[7] = {1, 2};

    // 9-10: medium-large
    test_cases[8] = {1000, 50};
    test_cases[9] = {5000, 10};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].first << " M=" << test_cases[i].second << "\n";
    }

    return 0;
}
