#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE original (large N, converged)
    test_cases[0] = 30;

    // 2-3: small N (visible difference)
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-5: medium N
    test_cases[3] = 3;
    test_cases[4] = 5;

    // 6-7: larger
    test_cases[5] = 8;
    test_cases[6] = 12;

    // 8-9: convergence test
    test_cases[7] = 15;
    test_cases[8] = 25;

    // 10: random
    test_cases[9] = (int)rand_ll(1, 20);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
