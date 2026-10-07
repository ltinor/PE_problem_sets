#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases: A B pairs
    vector<pair<ll,ll>> tests(10);
    
    tests[0] = {4, 10};     // sample from problem (R(d) < 4/10, d=12)
    tests[1] = {1, 2};      // R(d) < 1/2
    tests[2] = {1, 3};
    tests[3] = {2, 5};
    tests[4] = {3, 10};
    tests[5] = {1, 10};
    tests[6] = {7, 20};
    tests[7] = {100, 1000};
    tests[8] = {15499, 94744};  // PE original
    tests[9] = {1, 100};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with A=" << tests[i].first << " B=" << tests[i].second << "\n";
    }

    return 0;
}
