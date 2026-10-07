#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (d=5 from PE, avg ≈ 3.2102888889)
    test_cases[0] = 5;

    // 2-3: very small
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-6: small
    test_cases[3] = 3;
    test_cases[4] = 4;
    test_cases[5] = 6;

    // 7: edge - d=7 (largest direct computation)
    test_cases[6] = 7;

    // 8-10: known values
    test_cases[7] = 8;
    test_cases[8] = 10;
    test_cases[9] = 14; // Original PE problem

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with d = " << test_cases[i] << "\n";
    }

    return 0;
}
