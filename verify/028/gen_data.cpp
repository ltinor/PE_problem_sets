#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Generate 10 test cases (each with T test groups)
    struct TestCase {
        int T;
        vector<long long> Ns;
    };

    vector<TestCase> tests(10);

    // 1: sample - original PE problem: N=1001
    tests[0] = {1, {1001}};

    // 2: small N
    tests[1] = {1, {1}};

    // 3: small N
    tests[2] = {1, {3}};

    // 4: small N
    tests[3] = {1, {5}};

    // 5: medium
    tests[4] = {1, {101}};

    // 6: large
    tests[5] = {1, {1000001}};

    // 7: near max
    tests[6] = {1, {999999999}};

    // 8: max
    tests[7] = {1, {1000000000}};

    // 9: multiple small
    tests[8] = {3, {1, 3, 5}};

    // 10: mixed
    tests[9] = {3, {7, 1001, 500000001}};

    // Ensure all N are odd
    for (int i = 0; i < 10; i++) {
        for (auto& n : tests[i].Ns) {
            if (n % 2 == 0) n++;
        }

        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].T << "\n";
        for (auto n : tests[i].Ns) {
            fout << n << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }
    return 0;
}
