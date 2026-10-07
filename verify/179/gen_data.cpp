#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> test_cases = {
        10,        // N=10: small
        100,       // N=100
        1000,      // N=1000
        10000,     // N=10000
        100000,    // N=100000
        500000,    // N=500000
        1000000,   // N=1M
        5000000,   // N=5M
        10000000,  // N=10M, PE original
        9999999    // N=10M-1
    };

    for (int i = 0; i < (int)test_cases.size(); i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
