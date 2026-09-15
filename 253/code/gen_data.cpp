#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample from PE (N=10, avg ≈ 3.400732)
    test_cases[0] = 10;

    // 2-3: very small
    test_cases[1] = 2;
    test_cases[2] = 3;

    // 4-5: small (brute feasible)
    test_cases[3] = 4;
    test_cases[4] = 5;

    // 6-7: medium
    test_cases[5] = 8;
    test_cases[6] = 15;

    // 8: edge - N=1
    test_cases[7] = 1;

    // 9-10: large (up to original PE)
    test_cases[8] = 20;
    test_cases[9] = 40; // Original PE problem

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
