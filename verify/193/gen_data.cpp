#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (K=50, answer = 684465067343069)
    test_cases[0] = 50;

    // 2-3: small K for brute verification
    test_cases[1] = 1;   // N=2, answer=1
    test_cases[2] = 2;   // N=4, answer=3

    // 4-5: small-mid
    test_cases[3] = 5;   // N=32
    test_cases[4] = 10;  // N=1024

    // 6-8: medium-large
    test_cases[5] = 20;
    test_cases[6] = 30;
    test_cases[7] = 40;

    // 9: another large
    test_cases[8] = 45;

    // 10: random
    test_cases[9] = 5 + rand() % 46;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i] << "\n";
    }

    return 0;
}
