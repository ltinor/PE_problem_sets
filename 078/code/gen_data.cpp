#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample - M=7 (answer: p(5)=7, so n=5)
    test_cases[0] = 7;

    // 2-3: small M
    test_cases[1] = rand_int(2, 100);
    test_cases[2] = rand_int(10, 200);

    // 4-6: medium M
    test_cases[3] = rand_int(1000, 10000);
    test_cases[4] = rand_int(10000, 100000);
    test_cases[5] = rand_int(50000, 500000);

    // 7: small boundary
    test_cases[6] = 2;

    // 8: maximum boundary
    test_cases[7] = 1000000;

    // 9-10: random large
    test_cases[8] = rand_int(500000, 900000);
    test_cases[9] = rand_int(800000, 999999);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}
