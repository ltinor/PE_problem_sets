#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: PE sample (N=5e15, answer=4037526)
    test_cases[0] = 5000000000000000LL;

    // 2-3: small N
    test_cases[1] = 10;
    test_cases[2] = 100;

    // 4-5: medium
    test_cases[3] = 1000;
    test_cases[4] = 100000;
    test_cases[5] = 10000000;

    // 6-7: larger
    test_cases[6] = 1000000000LL;
    test_cases[7] = 100000000000LL;

    // 8-9: near PE range
    test_cases[8] = 100000000000000LL;
    test_cases[9] = 1000000000000000LL;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
