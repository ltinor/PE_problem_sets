#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (K=1, original PE answer: 5777)
    test_cases[0] = 1;

    // 2-3: small K
    for (int i = 1; i < 3; i++) {
        test_cases[i] = rand_int(1, 3);
    }

    // 4-6: medium K
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_int(4, 7);
    }

    // 7: max K
    test_cases[6] = 10;

    // 8: boundary K=1
    test_cases[7] = 1;

    // 9-10: random K
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_int(2, 10);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}
