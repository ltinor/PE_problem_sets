#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1. Sample: N=2 (verify A_10=13, A_100=3251)
    test_cases[0] = 2;

    // 2-3. Small
    test_cases[1] = 1;
    test_cases[2] = 3;

    // 4-6. Medium
    test_cases[3] = 4;
    test_cases[4] = 5;
    test_cases[5] = 6;

    // 7-8. Large
    test_cases[6] = 10;
    test_cases[7] = 12;

    // 9-10. PE problem: N=18
    test_cases[8] = 18;
    test_cases[9] = 18;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N=" << test_cases[i] << "\n";
    }
    return 0;
}
