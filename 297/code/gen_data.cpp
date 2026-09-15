#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: PE answer (N=1e17, answer=2252639041804718029)
    test_cases[0] = 100000000000000000LL;

    // 2-4: small
    test_cases[1] = 10;
    test_cases[2] = 100;
    test_cases[3] = 1000;

    // 5-6: medium
    test_cases[4] = 1000000; // known: 7894453
    test_cases[5] = 10000000;

    // 7-8: large
    test_cases[6] = 1000000000LL;
    test_cases[7] = 1000000000000LL;
    test_cases[8] = 1000000000000000LL;
    test_cases[9] = 10000000000000000LL;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
