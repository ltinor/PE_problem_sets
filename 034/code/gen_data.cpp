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

    // 1: N = 145 — only 145 itself (excluding 1,2)
    tests[0] = {1, {145}};

    // 2: N = 100 — none (145 > 100)
    tests[1] = {1, {100}};

    // 3: N = 1000 — 145
    tests[2] = {1, {1000}};

    // 4: N = 50000 — 145 + 40585 = 40730
    tests[3] = {1, {50000}};

    // 5: N = 1000000 — full answer 40730 (PE original)
    tests[4] = {1, {1000000}};

    // 6: N = 40585 — 145 + 40585 = 40730
    tests[5] = {1, {40585}};

    // 7: N = 200
    tests[6] = {1, {200}};

    // 8: multiple queries
    tests[7] = {3, {10, 145, 50000}};

    // 9: edge N=1
    tests[8] = {1, {1}};

    // 10: N=1000000 again
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
