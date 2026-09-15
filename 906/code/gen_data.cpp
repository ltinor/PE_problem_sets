#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));

    vector<int> test_cases(10);
    test_cases[0] = 3;   // 样例：P(3) = 17/18 ≈ 0.9444444444
    test_cases[1] = 1;
    test_cases[2] = 2;
    test_cases[3] = 4;
    test_cases[4] = 5;
    test_cases[5] = 6;
    test_cases[6] = 3;
    test_cases[7] = 6;
    test_cases[8] = 4;
    test_cases[9] = 5;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }
    return 0;
}
