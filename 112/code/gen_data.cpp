#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: P=50 → answer 538
    test_cases[0] = 50;

    // 2: P=90 → answer 21780
    test_cases[1] = 90;

    // 3: P=99 → answer 1587000 (original PE)
    test_cases[2] = 99;

    // 4: P=10
    test_cases[3] = 10;

    // 5: P=25
    test_cases[4] = 25;

    // 6: P=33
    test_cases[5] = 33;

    // 7: P=60
    test_cases[6] = 60;

    // 8: P=80
    test_cases[7] = 80;

    // 9: P=95
    test_cases[8] = 95;

    // 10: P=70
    test_cases[9] = 70;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with P = " << test_cases[i] << "\n";
    }

    return 0;
}
