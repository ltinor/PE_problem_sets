#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample from PE (i=1..20 → sum=156)
    test_cases[0] = 20;

    // 2-3: very small
    test_cases[1] = 5;
    test_cases[2] = 10;

    // 4-5: small-medium
    test_cases[3] = 30;
    test_cases[4] = 50;

    // 6-7: medium
    test_cases[5] = 80;
    test_cases[6] = 100;

    // 8: edge - N=1
    test_cases[7] = 1;

    // 9-10: large (up to original PE)
    test_cases[8] = 120;
    test_cases[9] = 150;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
