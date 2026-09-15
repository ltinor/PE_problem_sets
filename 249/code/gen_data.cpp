#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (PE original)
    test_cases[0] = 5000;

    // 2-3: small (brute-force feasible)
    test_cases[1] = 5;
    test_cases[2] = 10;

    // 4-5: medium-small
    test_cases[3] = 20;
    test_cases[4] = 30;

    // 6-7: medium
    test_cases[5] = 100;
    test_cases[6] = 500;

    // 8: edge - N=3 (primes: {2})
    test_cases[7] = 3;

    // 9-10: large
    test_cases[8] = 1000;
    test_cases[9] = 2000;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }

    return 0;
}
