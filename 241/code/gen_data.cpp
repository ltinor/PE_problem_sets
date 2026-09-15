#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: sample
    test_cases[0] = 100;

    // 2-3: small (N <= 1000)
    for (int i = 1; i < 3; i++)
        test_cases[i] = rand_ll(10, 1000);

    // 4-5: medium (N <= 10^5)
    for (int i = 3; i < 5; i++)
        test_cases[i] = rand_ll(1000, 100000);

    // 6-7: large (N <= 10^7)
    for (int i = 5; i < 7; i++)
        test_cases[i] = rand_ll(100000, 10000000);

    // 8: edge - N=1
    test_cases[7] = 1;

    // 9-10: maximum
    test_cases[8] = 50000000LL;
    test_cases[9] = 100000000LL;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
