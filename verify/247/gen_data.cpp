#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE original → k=3
    test_cases[0] = 3;

    // 2-3: small k for verification
    test_cases[1] = 0;
    test_cases[2] = 1;

    // 4-5: edge
    test_cases[3] = 2;
    test_cases[4] = 0;

    // 6-7: slightly larger
    test_cases[5] = 1;
    test_cases[6] = 2;

    // 8-10: medium
    test_cases[7] = 3;
    test_cases[8] = 2;
    test_cases[9] = 1;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i] << "\n";
    }

    return 0;
}
