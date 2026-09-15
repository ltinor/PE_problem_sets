#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (K=6, from original problem's first example)
    test_cases[0] = 6;

    // 2: K=8 (original PE answer)
    test_cases[1] = 8;

    // 3-5: small K (1-3)
    test_cases[2] = 1;
    test_cases[3] = 2;
    test_cases[4] = 3;

    // 6-7: medium K (4-5)
    test_cases[5] = 4;
    test_cases[6] = 5;

    // 8: K=7
    test_cases[7] = 7;

    // 9-10: random K from 3-7
    test_cases[8] = 3 + rand() % 5;
    test_cases[9] = 3 + rand() % 5;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
