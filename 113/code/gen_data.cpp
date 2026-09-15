#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: D=1 → all 1-digit numbers (1-9) are non-bouncy → 9
    test_cases[0] = 1;

    // 2: D=2
    test_cases[1] = 2;

    // 3: D=3
    test_cases[2] = 3;

    // 4: D=4
    test_cases[3] = 4;

    // 5: D=5
    test_cases[4] = 5;

    // 6: D=6 → answer 12951 (from PE description)
    test_cases[5] = 6;

    // 7: D=10 → answer 277032 (from PE description)
    test_cases[6] = 10;

    // 8: D=30
    test_cases[7] = 30;

    // 9: D=50
    test_cases[8] = 50;

    // 10: D=100 → original PE answer 51161058134250
    test_cases[9] = 100;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with D = " << test_cases[i] << "\n";
    }

    return 0;
}
