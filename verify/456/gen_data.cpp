#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases = {
        8,           // sample
        600,         // verification
        20,          // small
        100,         // small
        1000,        // medium
        5000,        // medium
        40000,       // large verification
        200000,      // large
        1000000,     // large
        2000000      // max
    };

    for (int i = 0; i < (int)test_cases.size(); i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
