#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (N=30, answer = 1918080160)
    test_cases[0] = 30;

    // 2: Sample N=4, answer = 43
    test_cases[1] = 4;

    // 3-4: small N
    test_cases[2] = 1;
    test_cases[3] = 2;

    // 5-7: medium
    test_cases[4] = 5;
    test_cases[5] = 10;
    test_cases[6] = 15;

    // 8-9: large
    test_cases[7] = 20;
    test_cases[8] = 25;

    // 10: random
    test_cases[9] = 8 + rand() % 23; // random 8..30

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }

    return 0;
}
