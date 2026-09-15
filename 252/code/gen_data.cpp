#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample from PE (N=20, max area = 1049694.5)
    test_cases[0] = 20;

    // 2-3: very small (brute feasible)
    test_cases[1] = 5;
    test_cases[2] = 8;

    // 4-5: small
    test_cases[3] = 10;
    test_cases[4] = 12;

    // 6-7: medium
    test_cases[5] = 30;
    test_cases[6] = 50;

    // 8: medium-large
    test_cases[7] = 100;

    // 9-10: large (up to original PE)
    test_cases[8] = 200;
    test_cases[9] = 500; // Original PE problem

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
