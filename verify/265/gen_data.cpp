#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample N=3 → 52
    test_cases[0] = 3;
    // 2: N=4
    test_cases[1] = 4;
    // 3: N=5 (original problem)
    test_cases[2] = 5;
    
    // 4-10: repeat for timing
    test_cases[3] = 3;
    test_cases[4] = 4;
    test_cases[5] = 3;
    test_cases[6] = 5;
    test_cases[7] = 4;
    test_cases[8] = 5;
    test_cases[9] = 5;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
