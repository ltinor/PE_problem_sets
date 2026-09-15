#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (R=1000, answer=-271248680)
    test_cases[0] = 1000;

    // 2-3: very small
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-5: small
    test_cases[3] = 3;
    test_cases[4] = 5;

    // 6-7: medium
    test_cases[5] = 10;
    test_cases[6] = 20;

    // 8-10: larger
    test_cases[7] = 50;
    test_cases[8] = 100;
    test_cases[9] = 200;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with R=" << test_cases[i] << "\n";
    }

    return 0;
}
