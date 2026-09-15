#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: PE answer check (U=1e9, answer=2209)
    test_cases[0] = 1000000000;

    // 2-3: small
    test_cases[1] = 10;
    test_cases[2] = 50;

    // 4-6: medium (known values)
    test_cases[3] = 100;
    test_cases[4] = 1000;
    test_cases[5] = 10000;

    // 7-8: larger
    test_cases[6] = 100000;
    test_cases[7] = 1000000;

    // 9-10: near PE
    test_cases[8] = 10000000;
    test_cases[9] = 100000000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with U = " << test_cases[i] << "\n";
    }

    return 0;
}
