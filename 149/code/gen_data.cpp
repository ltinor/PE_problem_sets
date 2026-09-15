#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (N=2000, answer=52852124)
    test_cases[0] = 2000;

    // 2-3: very small
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-5: small
    test_cases[3] = 5;
    test_cases[4] = 10;

    // 6-7: medium
    test_cases[5] = 20;
    test_cases[6] = 50;

    // 8-10: large
    test_cases[7] = 100;
    test_cases[8] = 500;
    test_cases[9] = 1000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }

    return 0;
}
