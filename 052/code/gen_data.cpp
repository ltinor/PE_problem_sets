#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: M=6 (original PE problem)
    test_cases[0] = 6;

    // 2-4: small M (2-4)
    test_cases[1] = 2;
    test_cases[2] = 3;
    test_cases[3] = 4;

    // 5: M=5
    test_cases[4] = 5;

    // 6-8: random M 2-5
    for (int i = 5; i < 8; i++) {
        test_cases[i] = 2 + rand() % 4;
    }

    // 9-10: M=6 duplication for verification and random 3-5
    test_cases[8] = 6;
    test_cases[9] = 2 + rand() % 4;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
