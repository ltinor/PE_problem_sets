#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: small (S=7 → example: score 6 has 11 ways, so score<7 has just those 11)
    test_cases[0] = 7;

    // 2-3: small
    test_cases[1] = 10;
    test_cases[2] = 20;

    // 4-5: medium
    test_cases[3] = 40;
    test_cases[4] = 60;

    // 6-7: larger
    test_cases[5] = 80;
    test_cases[6] = 90;

    // 8-9: random
    test_cases[7] = rand_int(30, 120);
    test_cases[8] = rand_int(50, 150);

    // 10: original PE (S=100) → 38182
    test_cases[9] = 100;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with S = " << test_cases[i] << "\n";
    }

    return 0;
}
