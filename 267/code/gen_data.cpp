#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases = {
        4,      // 01: very small (target unreachable)
        10,     // 02: small
        15,     // 03: small
        20,     // 04: small
        30,     // 05: medium small
        50,     // 06: medium
        1000,   // 07: PE verification case
        100,    // 08: medium
        200,    // 09: medium-large
        500,    // 10: large
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
