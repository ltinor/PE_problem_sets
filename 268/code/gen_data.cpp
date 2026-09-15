#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases = {
        1000,               // 01: sample from problem
        10000,              // 02: small
        100000,             // 03: small
        1000000,            // 04: medium small
        5000000,            // 05: medium
        10000000000LL,      // 06: large
        10000000000000000LL,// 07: PE verification (10^16)
        100000000000LL,     // 08: large
        1000000000000LL,    // 09: larger
        5000000000000000LL, // 10: near max
    };

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
