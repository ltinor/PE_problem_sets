#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(4);

    // 1: S=4 (PE original answer: 101524)
    test_cases[0] = 4;
    // 2: S=5
    test_cases[1] = 5;
    // 3: S=6 (PE original description: 102400)
    test_cases[2] = 6;
    // 4: S=4 again (boundary, verify consistency)
    test_cases[3] = 4;

    for (int i = 0; i < 4; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with S = " << test_cases[i] << "\n";
    }

    return 0;
}
