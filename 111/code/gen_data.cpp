#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: n=1 → sum of S(1,d) for d=0..9 (only d=2,3,5,7 produce primes)
    test_cases[0] = 1;

    // 2: n=2
    test_cases[1] = 2;

    // 3: n=3
    test_cases[2] = 3;

    // 4: sample n=4 → 273700
    test_cases[3] = 4;

    // 5: n=5
    test_cases[4] = 5;

    // 6: n=6
    test_cases[5] = 6;

    // 7-8: random
    test_cases[6] = rand_int(1, 7);
    test_cases[7] = rand_int(1, 8);

    // 9: n=9
    test_cases[8] = 9;

    // 10: original PE n=10 → 612407567715
    test_cases[9] = 10;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
