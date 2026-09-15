#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: PE answer check (N=1000000, answer=852938)
    test_cases[0] = 1000000;

    // 2-3: sample cases
    test_cases[1] = 5;
    test_cases[2] = 50;

    // 4-6: small
    test_cases[3] = 100;
    test_cases[4] = 500;
    test_cases[5] = 1000;

    // 7-8: medium
    test_cases[6] = 10000;
    test_cases[7] = 100000;

    // 9-10: larger
    test_cases[8] = 5000000;
    test_cases[9] = 10000000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
