#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (original PE: £2 = 200p)
    test_cases[0] = 200;

    // 2-3: small values
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_int(1, 500);
    }

    // 4-5: medium values
    for (int i = 3; i < 5; i++) {
        test_cases[i] = rand_int(1000, 10000);
    }

    // 6: max value
    test_cases[5] = 100000;

    // 7: boundary (1)
    test_cases[6] = 1;

    // 8-10: random
    for (int i = 7; i < 10; i++) {
        test_cases[i] = rand_int(5000, 100000);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }

    return 0;
}
