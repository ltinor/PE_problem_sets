#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (N=3 → 74)
    test_cases[0] = 3;

    // 2-3: small (N=1,2)
    test_cases[1] = 1;
    test_cases[2] = 2;

    // 4-5: medium (N=4,5)
    test_cases[3] = 4;
    test_cases[4] = 5;

    // 6-7: large (N=8,9)
    test_cases[5] = 8;
    test_cases[6] = 9;

    // 8-9: random
    test_cases[7] = rand_int(1, 7);
    test_cases[8] = rand_int(1, 10);

    // 10: original PE problem (N=10)
    test_cases[9] = 10;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
