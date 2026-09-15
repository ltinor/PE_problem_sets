#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct TestCase {
        int T;
        vector<pair<int,int>> cases;
    };

    vector<TestCase> tests(10);

    // 1: sample - original PE problem: a,b up to 5 → answer 15? No.
    // Original: a,b in [2,5] → 2^2=4, 2^3=8, 2^4=16, 2^5=32, 3^2=9, 3^3=27, 3^4=81, 3^5=243, 4^2=16(dup), 4^3=64, 4^4=256, 4^5=1024, 5^2=25, 5^3=125, 5^4=625, 5^5=3125 → 15
    // Original bounds: 2..100 → answer 9183
    tests[0] = {1, {{5, 5}}};

    // 2: small
    tests[1] = {1, {{10, 10}}};

    // 3: medium
    tests[2] = {1, {{30, 30}}};

    // 4: original bound
    tests[3] = {1, {{100, 100}}};

    // 5: asymmetric
    tests[4] = {1, {{100, 50}}};

    // 6: asymmetric 2
    tests[5] = {1, {{50, 100}}};

    // 7: small edge
    tests[6] = {1, {{2, 2}}};

    // 8: max
    tests[7] = {1, {{100, 100}}};

    // 9: multiple cases
    tests[8] = {3, {{5, 5}, {10, 10}, {20, 20}}};

    // 10: mixed
    tests[9] = {2, {{2, 100}, {100, 2}}};

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
