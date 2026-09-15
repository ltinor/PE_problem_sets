#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll rand_ll(ll l, ll r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases;

    // 1: sample N=1000
    cases.push_back(1000);

    // 2: N=5000
    cases.push_back(5000);

    // 3: N=10000
    cases.push_back(10000);

    // 4: N=100000
    cases.push_back(100000);

    // 5: N=500000
    cases.push_back(500000);

    // 6: N=1000000
    cases.push_back(1000000);

    // 7: PE original N=100000000 → ans=2906969179
    cases.push_back(100000000);

    // 8-10: random
    cases.push_back(rand_ll(2000000, 10000000));
    cases.push_back(rand_ll(15000000, 50000000));
    cases.push_back(rand_ll(60000000, 99900000));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << cases[i] << "\n";
    }

    return 0;
}
