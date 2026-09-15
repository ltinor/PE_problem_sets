#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: K=1
    test_cases[0] = 1;
    // 2: K=2
    test_cases[1] = 2;
    // 3: K=3
    test_cases[2] = 3;
    // 4: K=4 (original problem)
    test_cases[3] = 4;
    
    // 5-10: duplicate some for timing
    test_cases[4] = 1;
    test_cases[5] = 2;
    test_cases[6] = 1;
    test_cases[7] = 3;
    test_cases[8] = 2;
    test_cases[9] = 4;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
