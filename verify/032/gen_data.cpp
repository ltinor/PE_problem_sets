#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (original PE: N=9)
    test_cases[0] = 9;

    // 2: N=5
    test_cases[1] = 5;

    // 3: N=6
    test_cases[2] = 6;

    // 4: N=7
    test_cases[3] = 7;

    // 5: N=8
    test_cases[4] = 8;

    // 6: N=4
    test_cases[5] = 4;

    // 7: N=3
    test_cases[6] = 3;

    // 8: N=1
    test_cases[7] = 1;

    // 9: N=2
    test_cases[8] = 2;

    // 10: N=9 (duplicate for verification)
    test_cases[9] = 9;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
