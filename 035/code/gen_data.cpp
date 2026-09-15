#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct TestCase {
        int T;
        vector<int> Ns;
    };

    vector<TestCase> tests(10);

    // 1: N = 100 — 13 circular primes
    tests[0] = {1, {100}};

    // 2: N = 10 — 4 circular primes (2,3,5,7)
    tests[1] = {1, {10}};

    // 3: N = 1000
    tests[2] = {1, {1000}};

    // 4: N = 1000000 — PE original: 55
    tests[3] = {1, {1000000}};

    // 5: N = 500000
    tests[4] = {1, {500000}};

    // 6: N = 200
    tests[5] = {1, {200}};

    // 7: N = 10000
    tests[6] = {1, {10000}};

    // 8: multiple queries
    tests[7] = {4, {2, 10, 100, 1000000}};

    // 9: N = 100000
    tests[8] = {1, {100000}};

    // 10: N = 1000000 again
    tests[9] = {1, {1000000}};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].T << "\n";
        for (int n : tests[i].Ns) {
            fout << n << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }
    return 0;
}
