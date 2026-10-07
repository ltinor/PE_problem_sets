#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct TestCase {
        int T;
        vector<int> Ks;
    };

    vector<TestCase> tests(10);

    // 1: sample - original PE problem: K=4 → sum = 19316? Let me check
    // Actually: 1634=1^4+6^4+3^4+4^4, 8208=8^4+2^4+0^4+8^4, 9474=9^4+4^4+7^4+4^4
    // sum = 1634+8208+9474 = 19316
    tests[0] = {1, {4}};

    // 2: K=5 (original problem)
    tests[1] = {1, {5}};

    // 3: K=3
    tests[2] = {1, {3}};

    // 4: K=6
    tests[3] = {1, {6}};

    // 5: K=2
    tests[4] = {1, {2}};

    // 6: K=4 again (verify)
    tests[5] = {1, {4}};

    // 7: K=5 again
    tests[6] = {1, {5}};

    // 8: multiple K
    tests[7] = {3, {3, 4, 5}};

    // 9: all K 2..6
    tests[8] = {5, {2, 3, 4, 5, 6}};

    // 10: K=6
    tests[9] = {1, {6}};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].T << "\n";
        for (int k : tests[i].Ks) {
            fout << k << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }
    return 0;
}
