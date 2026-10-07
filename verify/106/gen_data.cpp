#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample n=4 → answer 1
    test_cases[0] = 4;

    // 2: sample n=7 → answer 70
    test_cases[1] = 7;

    // 3-4: small
    test_cases[2] = 2;
    test_cases[3] = 3;

    // 5-6: medium
    test_cases[4] = 5;
    test_cases[5] = 6;

    // 7-8: random
    test_cases[6] = rand_int(2, 10);
    test_cases[7] = rand_int(2, 11);

    // 9: near max
    test_cases[8] = 11;

    // 10: original PE (n=12) → 21384
    test_cases[9] = 12;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
