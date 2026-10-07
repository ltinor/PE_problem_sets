#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample S=100 (original problem)
    test_cases[0] = 100;

    // 2: sample S=10
    test_cases[1] = 10;

    // 3-5: small S
    test_cases[2] = 1;
    test_cases[3] = 5;
    test_cases[4] = 20;

    // 6-8: medium
    test_cases[5] = 30;
    test_cases[6] = 50;
    test_cases[7] = 75;

    // 9-10: boundary
    test_cases[8] = 90;
    test_cases[9] = 100;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with S = " << test_cases[i] << "\n";
    }

    return 0;
}
