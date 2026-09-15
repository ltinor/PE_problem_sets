#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    vector<int> test_cases(10);

    // Various precision levels
    test_cases[0] = 1000;   // low precision
    test_cases[1] = 2000;
    test_cases[2] = 5000;
    test_cases[3] = 10000;
    test_cases[4] = 20000;
    test_cases[5] = 50000;
    test_cases[6] = 100000;
    test_cases[7] = 200000;
    test_cases[8] = 500000;  // high precision - PE quality
    test_cases[9] = 1000000; // maximum precision

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with steps=" << test_cases[i] << "\n";
    }
    return 0;
}
