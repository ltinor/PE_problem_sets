#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Generate 10 test cases (each with T test groups)
    struct TestCase {
        int T;
        vector<pair<int,int>> cases;
    };

    vector<TestCase> tests(10);

    // 1: sample - original PE problem: n²+n+41 (a=1, b=41), A=42, B=42 → a=-1? No, a=1.
    // Original: |a|<1000, |b|≤1000 → a=-61, b=971 → product = -59231
    tests[0] = {1, {{42, 42}}};

    // 2: small with known example
    tests[1] = {1, {{50, 50}}};

    // 3: medium
    tests[2] = {1, {{100, 100}}};

    // 4: original bound
    tests[3] = {1, {{1000, 1000}}};

    // 5: asymmetric small
    tests[4] = {1, {{30, 100}}};

    // 6: asymmetric medium
    tests[5] = {1, {{100, 500}}};

    // 7: near max
    tests[6] = {1, {{999, 1000}}};

    // 8: multiple cases
    tests[7] = {3, {{42, 42}, {100, 100}, {50, 80}}};

    // 9: edge small
    tests[8] = {1, {{10, 10}}};

    // 10: edge - one case at 1000,1000 plus small
    tests[9] = {2, {{10, 10}, {1000, 1000}}};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].T << "\n";
        for (auto& p : tests[i].cases) {
            fout << p.first << " " << p.second << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }
    return 0;
}
